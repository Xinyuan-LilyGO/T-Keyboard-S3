/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-11-10 11:56:21
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-10 15:17:53
 * @License: GPL 3.0
 */
#include "Arduino_GFX_Library.h"
#include "gameover.h"
#include "noInternet.h"
#include "imgData.h"
#include "config.h"
#include "pin_config.h"
#include "T-Keyboard_S3_Drive.h"

#define key1_pin 46
#define key2_pin 3

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

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32SPI(
    N085_DC /* DC */, -1 /* CS */, N085_SCLK /* SCK */, N085_MOSI /* MOSI */, -1 /* MISO */); // Software SPI

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_GC9107(
    bus, N085_RST /* RST */, 0 /* rotation */, true /* IPS */,
    128 /* width */, 128 /* height */,
    2 /* col offset 1 */, 1 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

Arduino_GFX *img = new Arduino_Canvas(128 /* width */, 128 /* height */, gfx);
Arduino_GFX *img2 = new Arduino_Canvas(50 /* width */, 128 /* height */, gfx);
Arduino_GFX *e = new Arduino_Canvas(eW /* width */, eH /* height */, gfx);
Arduino_GFX *e2 = new Arduino_Canvas(eW /* width */, eH /* height */, gfx);

void key1_isr(void)
{
    key_text = 1;
}

void key2_isr(void)
{
    key_text = 2;
}

void exti_init(void)
{
    pinMode(key1_pin, INPUT_PULLUP); // 设置引脚为输入上拉模式
    pinMode(key2_pin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(key1_pin), key1_isr, FALLING); // 设置下降沿触发
    attachInterrupt(digitalPinToInterrupt(key2_pin), key2_isr, FALLING);
}

void drawS(int x, int y, int frame)
{
    img->fillScreen(WHITE);
    img->drawLine(0, 84, 320, 84, BLACK);

    for (int i = 0; i < 6; i++)
    {
        img->drawLine(linesX[i], 100, linesX[i] + linesW[i], 100, BLACK);
        linesX[i] = linesX[i] - roll_speed;
        if (linesX[i] < -14)
        {
            linesX[i] = random(245, 320);
            linesW[i] = random(1, 14);
        }
        img->drawLine(linesX2[i], 98, linesX2[i] + linesW2[i], 98, BLACK);
        linesX2[i] = linesX2[i] - roll_speed;
        if (linesX2[i] < -14)
        {
            linesX2[i] = random(245, 320);
            linesW2[i] = random(1, 14);
        }
    }

    for (int j = 0; j < 2; j++)
    { // 云朵随机生成2
        img->drawXBitmap(clouds[j], 20, cloud, 38, 11, BLACK);
        clouds[j] = clouds[j] - cloudSpeed;
        if (clouds[j] < -40)
            clouds[j] = random(320, 364);
    }

    for (int n = 0; n < 2; n++)
    {
        img->drawXBitmap(bumps[n], 80, bump[bumpsF[n]], 34, 5, BLACK);
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

    e->drawXBitmap(0, 0, enemy[0], eW, eH, BLACK);
    e2->drawXBitmap(0, 0, enemy[1], eW, eH, BLACK);
    img2->fillScreen(WHITE);
    img2->drawXBitmap(0, 0, dino[frame], 33, 35, BLACK);

    e->flush(eX[0], 56);
    e2->flush(eX[1], 56);
    img2->flush(x, y);

    // score = (millis() - start_t) / 120;
    // img->setTextSize(1);
    // img->setCursor(80, 0);
    // img->printf("%d", score);
    // img->setCursor(40, 0);
    // img->printf("%.2f", roll_speed);
    // img->flush();

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
            gfx->fillRect(0, 30, 320, 110, WHITE);               // 碰到障碍物结束画面的填充
            gfx->drawXBitmap(45, 35, gameover, 223, 100, BLACK); //;结束的画面
            delay(500);
        }
    }
}

void setup()
{
    pinMode(N085_BL, OUTPUT);

    ledcAttachPin(N085_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, 255); // brightness 0 - 255

    N085_Screen_Set(N085_Initialize);
    N085_Screen_Set(N085_Screen_ALL);

    gfx->begin();
    gfx->fillScreen(BLACK);

    img->begin();
    img2->begin();
    e->begin();
    e2->begin();

    img->setTextColor(BLACK, WHITE);
    img->flush();

    exti_init();

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
    gfx->draw16bitBeRGBBitmap(0, 0, (uint16_t *)noInternet, 217, 135); // 没有网络的画面
}

void loop()
{
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
            gfx->fillScreen(WHITE);
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
