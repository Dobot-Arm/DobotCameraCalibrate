#include "DError.h"

QString DError::getErrMsg(int code, const QString& strMsg)
{
    if (!strMsg.isEmpty()) return strMsg;
    QString str;
    switch(code)
    {
    case DT_NO_ERROR:break;
    case DT_ERR_INVALID_REQUEST:
        str="invalid request.";break;
    case DT_ERR_INVALID_PARAMS:
        str="invalid params.";break;
    case DT_ERR_INVALID_METHOD:
        str="invalid method.";break;
    case DT_ERR_INVALID_PLUGIN:
        str="invalid plugin.";break;
    case DT_ERR_LIB_FUNC_DT_ERR_LOAD:
        str = "load library function error";break;
    case DT_ERR_SAVE_FILE:
        str = "save file fail";break;
    case DT_ERR_OPEN_FILE:
        str = "open file fail";break;
    case DT_ERR_CREATE_FILE:
        str = "create file fail";break;
    case DT_ERR_READ_FILE:
        str = "read file fail";break;
    case DT_ERR_WRITE_FILE:
        str = "write file fail";break;
    case DT_ERR_FILE_NOT_EXIST:
        str = "file not exist";break;
    case DT_ERR_NOT_CONNECT:
        str = "device may be not connected/open";break;
    case DT_ERR_ILLEGAL_OPERATE_OTHER_DEVICE:
        str = "Illegal operation other's device";break;
    case DT_ERR_ALLOCATE_MEMORY:
        str = "can not allocate memory";break;
    case DT_ERR_CONTENT:
        str = "the content is error";break;
    case DT_ERR_PARAM_OUT_RANGE:
        str = "the parameter out of range";
        break;

    /**************************************************************/
    case DT_ERR_CONNECT_CAMERA:
        str = "connect camera fail";break;
    case DT_ERR_DISCONNECT_CAMERA:
        str = "disconnect camera fail";break;
    case DT_ERR_START_VIDEO:
        str = "start vide fail";break;
    case DT_ERR_STOP_VIDEO:
        str = "stop vide fail";break;
    case DT_ERR_TAKE_PHOTO:
        str = "take photo fail";break;
    case DT_ERR_CALIBRATE_POS:
        str = "get calibrate position fail";break;
    case DT_ERR_CALIBRATE_RESULT:
        str = "can not get calibrate result";break;
    case DT_ERR_CALIBRATE_FILE:
        str = "can not create calibrate file";break;
    case DT_ERR_USER_COORDINATE:
        str = "can not create user coordinate";break;
    case DT_ERR_CALIBRATE_BEGIN:
        str = "begin calibrate fail";break;
    case DT_ERR_CALIBRATE_END:
        str = "end calibrate fail";break;
    case DT_ERR_CALIBRATE_SAMPLING:
        str = "calibrate sampling fail";break;
    case DT_ERR_UPDATE_CALIBRATE_SAMPLING:
        str = "update calibrate sampling fail";break;
    case DT_ERR_SET_CAMERA_IP:
        str = "set ip config fail";break;
    case DT_ERR_GSET_TYPE_VALUE:
        str = "get/set type value fail";break;
    case DT_ERR_SEARCH_CAMERA:
        str = "search camera fail";break;

    /**************************************************************/
    case DT_ERR_IODEVICE_OPEN:
        str = "io device open fail";break;
    case DT_ERR_IODEVICE_GETLIGHTBOARDPARAM:
        str = "io device get light param fail";break;
    case DT_ERR_IODEVICE_GETVERSION:
        str = "io device get version fail";break;
    case DT_ERR_IODEVICE_TURNLIGHTON:
        str = "turn light on fail";break;
    case DT_ERR_IODEVICE_TURNLIGHTOFF:
        str = "turn light off fail";break;
    default:
        str = QString("unknow error,errcode=%1").arg(code);
    }
    return str;
}
