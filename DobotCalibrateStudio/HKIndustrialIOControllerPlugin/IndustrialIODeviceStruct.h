#ifndef INDUSTRIALIODEVICESTRUCT_H
#define INDUSTRIALIODEVICESTRUCT_H

#include <cstdint>
/*
#pragma pack(1)
.......
#pragma pack()
*/

/** @enum MV_IO_LIGHTSTATE
 *  @brief ch:光源常亮常灭 | en: Light states
 */
typedef enum MV_IO_LIGHTSTATE__
{
    MV_IO_LIGHTSTATE_ON         = 0x0001,       // ch:触发后常亮 | en:Light on after triggering
    MV_IO_LIGHTSTATE_OFF        = 0x0002,       // ch:触发后常灭 | en:Light off after triggering
} MV_IO_LIGHTSTATE;

/** @struct MV_IO_VERSION
 *  @brief ch:SDK版本号 | en:SDK vision
 */
typedef struct MV_IO_VERSION__
{
    unsigned int    nMainVersion;   // ch:主版本号 | en:Major version
    unsigned int    nSubVersion;    // ch:次版本号 | en:Minor version
    unsigned int    nModifyVersion; // ch:修订版本号 | en:Revision
    unsigned int    nYear;          // ch:年 | en:Year
    unsigned int    nMonth;         // ch:月 | en:month
    unsigned int    nDay;           // ch:日 | en:date
    unsigned int    nReserved[8];   // ch:保留字节 | en:Reserved
}MV_IO_VERSION;

/** @struct MV_IO_LIGHT_PARAM
 *  @brief ch:亮度参数设置 | en:Parameter setting of light source module
 */
typedef struct MV_IO_LIGHT_PARAM__
{
    unsigned char               nPortNumber;            // ch:亮度端口 | en:Light port
    unsigned short              nLightValue;            // ch:光源亮度值(0-100之间) | en:Light value(0-100)
    unsigned short              nLightState;            // ch:触发后常亮还是常灭 | en:Light on or off after triggering
    unsigned short              nLightEdge;             // ch:上升沿触发还是下降沿触发 | en:Rising  or falling edge trigger
    unsigned int                nDurationTime;          // ch:持续时间 | en:Duration Time
    unsigned int                nReserved[3];           // ch:保留字段 | en:Reserved
} MV_IO_LIGHT_PARAM;

#endif // INDUSTRIALCAMERASTRUCT_H
