#ifndef __MAVRCP_H__
#define __MAVRCP_H__

#include <stdlib.h>

/* av render info */
struct _tAVRInfo
{
    char avr_uuid[128];
    char avr_name[128];
};

enum _ePlayStateEnum
{
    MAVRCP_PLAYING=0,                        // ������
    MAVRCP_STOPPED,                          // ��ֹͣ
    MAVRCP_PAUSED,                           // ����ͣ
    MAVRCP_RECORDING,                        // ¼����
    MAVRCP_TRANSITIONING,                    // ������
    MAVRCP_NO_MEDIA,                         // ���ļ�
    MAVRCP_UNKNOWN                           // δ֪
};

/* play mode enum */
enum _ePlayModeEnum
{
    MAVRCP_INVALID       =0x0000000,         // ��Ч
    MAVRCP_NORMAL        =0x0000001,         // ��������
    MAVRCP_REPEAT_ALL    =0x0000002,         // �ظ�����
    MAVRCP_REPEAT_ONE    =0x0000004,         // �����ظ�
    MAVRCP_RANDOM        =0x0000008,         // �������
    MAVRCP_SHUFFLE       =0x0000010,         // 
    MAVRCP_INTRO         =0x0000020          // 
};

/* render state info */
struct _tRenderStateInfo
{
    int CMID;
    int AVTID;
    int RCID;

    int Error;

    char *ProtocolInfo;
    char *MediaUri;
    char *TrackUri;
    char *TransportStatus;
    unsigned int TotalTracks;
    unsigned int TrackNumber;
    enum _ePlayStateEnum PlayState;
    enum _ePlayModeEnum PlayMode;

    unsigned int Duration;

    char TrackPosition[32];

    char **SupportedRecordQualityModes;
    int SupportedRecordQualityModesLength;

    char **RecordMedia;
    int RecordMediaLength;

    char **PlayMedia;
    int PlayMediaLength;

    int ChannelCount;
    char **Channel;

    char *Volume;
    int *Mute;
};

/* callback functions declared */
typedef void (* Callback_AVRenderSink)( char * udn, char * friendlyname);
typedef void (* Callback_AVRenderUpdateSink)( char * udn, char * friendlyname, struct _tRenderStateInfo renderstate);

typedef void (* Callback_CommonSink)( int ErrorCode);
typedef void (* Callback_GetDevCapSink)( int ErrorCode, char* PlayMedia, char* RecMedia, char* RecQualityModes);
typedef void (* Callback_GetMediaInfoSink)( int ErrorCode, int nrTracks, int mediaDuration, char * curUrI, char * nextURI);
typedef void (* Callback_GetPositionSink)( int ErrorCode, int RelativeSeconds, int AbsoluteSeconds, int RelativeCounter, int AbsoluteCounter);

/* callback functions define */
extern Callback_AVRenderSink           avrender_add         ;
extern Callback_AVRenderSink           avrender_del         ;
extern Callback_AVRenderUpdateSink     avrender_update      ;
extern Callback_GetDevCapSink          getdevcap_callback   ;
extern Callback_CommonSink             play_callback        ;
extern Callback_CommonSink             seek_callback        ;
extern Callback_CommonSink             stop_callback        ;
extern Callback_CommonSink             pause_callback       ;
extern Callback_CommonSink             next_callback        ;
extern Callback_CommonSink             prev_callback        ;
extern Callback_CommonSink             seturi_callback      ;
#if defined(INCLUDE_FEATURE_VOLUME)
extern Callback_CommonSink             setvol_callback      ;
extern Callback_CommonSink             setmute_callback     ;
#endif
extern Callback_CommonSink             setplaymode_callback ;
extern Callback_GetMediaInfoSink       getmediainfo_callback;
extern Callback_GetPositionSink        getposition_callback ;

/************************************************************************/
/* Interface                                                            */
/************************************************************************/
void printDmrList();
char * getDlnaDoc( char * udn );
char * getDlnaCap( char * udn );
void getDevCap( char * udn );
int supportPlayMode( char * udn, enum _ePlayModeEnum playmode );
int supportVolume( char * udn );
int supportMute( char * udn );
void play( char * udn );
void seek( char * udn, int pos );
void stop( char * udn );
void pause( char * udn );
void next( char * udn );
void prev( char * udn );
void setUri( char * udn, char * uri );
#if defined(INCLUDE_FEATURE_VOLUME)
void setVolume( char * udn, int vol );
void setMute( char * udn, int ismute );
#endif
void setPlayMode( char * udn, enum _ePlayModeEnum playmode );
void getMediaInfo( char * udn );
void getPosition( char * udn );

/************************************************************************/
/* Interface                                                            */
/************************************************************************/
int startAVRCP(int threadpool_size);
void stopAVRCP();

#endif // __MAVRCP_H__
