/*
  K1/IO10 - start
  K1/IO6 - jump
*/
#include "custom.h"
#include "./Google_Dinosaur/gameover.h"
#include "./Google_Dinosaur/noInternet.h"
#include "./Google_Dinosaur/imgData.h"
#include "./Google_Dinosaur/config.h"
#include "pin_config.h"
#include "T-Keyboard_S3_Drive.h"

TFT_eSprite *img = new TFT_eSprite(tft);
TFT_eSprite *img2 = new TFT_eSprite(tft);
TFT_eSprite *e = new TFT_eSprite(tft);
TFT_eSprite *e2 = new TFT_eSprite(tft);

String inputString = "";     // a String to hold incoming data
bool stringComplete = false; // whether the string is complete

int dinoW = 33;
int dinoH = 35;
float linesX[6];
int linesW[6];
float linesX2[6];
int linesW2[6];
float clouds[2] = {(float)random(0, 80), (float)random(100, 180)};
float bumps[2];
int bumpsF[2];
int eW = 18;
int eH = 38;

float eX[2] = {(float)random(240, 310), (float)random(380, 460)};
int ef[2] = {0, 1};

float roll_speed = GAME_SPEED;
float cloudSpeed = 0.4;
int x = 30;
int y = 58;
float dir = -1.4;
int frames = 0;
int f = 0;
bool gameRun = 0;
int score = 0;
unsigned long start_t = 0;
int t = 0;
bool button_jump = 0;
bool button_start = 0;

unsigned char key_text = 0;

void drawS(int x, int y, int frame)
{
    img->fillSprite(TFT_WHITE);
    img->drawLine(0, 84, 320, 84, TFT_BLACK);

    for (int i = 0; i < 6; i++)
    {
        img->drawLine(linesX[i], 100, linesX[i] + linesW[i], 100, TFT_BLACK);
        linesX[i] = linesX[i] - roll_speed;
        if (linesX[i] < -14)
        {
            linesX[i] = random(245, 320);
            linesW[i] = random(1, 14);
        }
        img->drawLine(linesX2[i], 98, linesX2[i] + linesW2[i], 98, TFT_BLACK);
        linesX2[i] = linesX2[i] - roll_speed;
        if (linesX2[i] < -14)
        {
            linesX2[i] = random(245, 320);
            linesW2[i] = random(1, 14);
        }
    }

    for (int j = 0; j < 2; j++)
    { // 云朵随机生成2
        img->drawXBitmap(clouds[j], 20, cloud, 38, 11, TFT_BLACK, TFT_WHITE);
        clouds[j] = clouds[j] - cloudSpeed;
        if (clouds[j] < -40)
            clouds[j] = random(320, 364);
    }

    for (int n = 0; n < 2; n++)
    {
        img->drawXBitmap(bumps[n], 80, bump[bumpsF[n]], 34, 5, TFT_BLACK, TFT_WHITE);
        bumps[n] = bumps[n] - roll_speed;
        if (bumps[n] < -40)
        {
            bumps[n] = random(320, 364);
            bumpsF[n] = random(0, 2);
        }
    }

    for (int m = 0; m < 2; m++)
    {

        eX[m] = eX[m] - roll_speed;
        if (eX[m] < -30)
            eX[m] = random(320, 364);
        ef[m] = random(0, 2);
    }

    e->drawXBitmap(0, 0, enemy[0], eW, eH, TFT_BLACK, TFT_WHITE);
    e2->drawXBitmap(0, 0, enemy[1], eW, eH, TFT_BLACK, TFT_WHITE);
    img2->drawXBitmap(0, 0, dino[frame], 33, 35, TFT_BLACK, TFT_WHITE);

    e->pushToSprite(img, eX[0], 56, TFT_WHITE);
    e2->pushToSprite(img, eX[1], 56, TFT_WHITE);
    img2->pushToSprite(img, x, y, TFT_WHITE);

    score = (millis() - start_t) / 120;
    img->drawString(String(score), 80, 0, 2);
    img->drawString(String(roll_speed), 40, 0, 2);
    img->pushSprite(0, 5);

    if (score > t + GAME_SPEEDUP_SCORE)
    {
        t = score;
        roll_speed = roll_speed + GAME_SPEEDUP_GAP;
    }
}

void checkColision()
{
    for (int i = 0; i < 2; i++)
    {
        if (eX[i] < x + dinoW / 2 && eX[i] > x && y > 25)
        {
            gameRun = 0;
            tft->fillRect(0, 30, 320, 110, TFT_WHITE);                          // 碰到障碍物结束画面的填充
            tft->drawXBitmap(45, 35, gameover, 223, 100, TFT_BLACK, TFT_WHITE); //;结束的画面
            delay(500);
        }
    }
}

void Google_Dinosaur_Initialization(void)
{
    N085_Screen_Set(N085_Screen_ALL);

    tft->setSwapBytes(true);
    tft->fillScreen(TFT_WHITE);
    img->setTextColor(TFT_BLACK, TFT_WHITE);
    img->setColorDepth(1);
    img2->setColorDepth(1);
    e->setColorDepth(1);
    e2->setColorDepth(1);

    img->createSprite(128, 128); // 整体画面
    img2->createSprite(33, 35);  // 恐龙画面
    e->createSprite(eW, eH);     // 障碍物1
    e2->createSprite(eW, eH);    // 障碍物2
    tft->fillScreen(TFT_WHITE);  // 整体填充颜色

    for (int i = 0; i < 6; i++)
    {
        linesX[i] = random(i * 60, (i + 1) * 60);
        linesW[i] = random(1, 14);
        linesX2[i] = random(i * 60, (i + 1) * 60);
        linesW2[i] = random(1, 14);
    }

    for (int n = 0; n < 2; n++)
    {
        bumps[n] = random(n * 100, (n + 1) * 120);
        bumpsF[n] = random(0, 2);
    }
    tft->pushImage(0, 0, 217, 135, noInternet); // 没有网络的画面

    My_UI.Window_Unlock_Flag = true;
}

void Google_Dinosaur_Loop(void)
{
    if (T_Keyboard_S3_Key_Trigger() != 0)
    {
        key_text = T_Keyboard_S3_Key_Trigger();
    }

    if (gameRun == 1)
    {
        if (key_text == 2)
        {
            f = 0;
        }

        if (key_text == 2)
        {
            y = y + dir * roll_speed;
            if (y <= 2)
            {
                y = 2;
                dir = dir * -1.00;
            }
            else if (y >= 58)
            {
                key_text = 0;
                dir = dir * -1.00;
            }
        }

        if (frames < 9 && key_text == 0)
        {
            f = 1;
        }
        if (frames > 9 && key_text == 0)
        {
            f = 2;
        }

        drawS(x, y, f);
        frames++;
        if (frames == 16)
            frames = 0;

        checkColision();
    }

    if (key_text == 1)
    {
        key_text = 0;
        if (gameRun == 0)
        {
            gameRun = 1;
            start_t = millis();
            tft->fillScreen(TFT_WHITE);
            eX[0] = random(240, 310);
            eX[1] = random(380, 460);
            key_text = 0;
            x = 30;
            y = 58;
            dir = -1.4;
            roll_speed = GAME_SPEED;
        }
    }
}
