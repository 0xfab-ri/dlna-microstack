#include "MAVRCP.h"

#include "MicroAVRCP.h"
#include "DMRCP_ControlPoint.h"

struct _tDmrInfo
{
    void * dmr_token;
    void * render;
} DmrInfo;

struct _tMAVRCP
{
    sem_t mavrcp_lock;
    void * mavrcp_dmr_tables;
    struct _tDmrInfo * mavrcp_dmr_info;

    void * mavrcp_stackchain;
    void * mavrcp_threadpool;
    void * mavrcp_rendercp;
};

/************************************************************************/
/* Callback Functions                                                   */
/************************************************************************/

void OnGetDevCapSink(struct AVRendererConnection * avrc,int ErrorCode, void *Tag, char* PlayMedia,char* RecMedia,char* RecQualityModes)
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "Success!\n" );
        printf( "PlayMedia:%s\n", PlayMedia );
        printf( "RecMedia:%s\n", RecMedia );
        printf( "RecQualityModes:%s\n", RecQualityModes );
    }
#endif

    if ( getdevcap_callback != NULL )
    {
        getdevcap_callback(ErrorCode, PlayMedia, RecMedia, RecQualityModes);
    }
}

void OnPlaySink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnPlaySink: Success!\n", ErrorCode );
        printf( "ProtocolInfo:%s\n", avrc->ProtocolInfo );	
        printf( "MediaUri:%s\n", avrc->MediaUri );	
        printf( "TrackUri:%s\n", avrc->TrackUri );
    }
#endif

    if ( play_callback != NULL )
    {
        play_callback(ErrorCode);
    }

}

void OnSeekSink(struct AVRendererConnection * avrc,int ErrorCode, void *Tag)
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnSeekSink: Success!\n", ErrorCode );
    }
#endif

    if ( seek_callback != NULL )
    {
        seek_callback(ErrorCode);
    }
}

void OnStopSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnStopSink: Success!\n", ErrorCode );
    }
#endif

    if ( stop_callback != NULL )
    {
        stop_callback(ErrorCode);
    }

}

void OnPauseSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnPauseSink: Success!\n", ErrorCode );
    }
#endif

    if ( pause_callback != NULL )
    {
        pause_callback(ErrorCode);
    }
}

void OnNextSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnNextSink: Success!\n", ErrorCode );
    }
#endif

    if ( next_callback != NULL )
    {
        next_callback(ErrorCode);
    }
}

void OnPrevSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnPrevSink: Success!\n", ErrorCode );
    }
#endif

    if ( prev_callback != NULL )
    {
        prev_callback(ErrorCode);
    }
}

void OnSetUriSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnSetUriSink: Success!\n", ErrorCode );
    }
#endif

    if ( seturi_callback != NULL )
    {
        seturi_callback(ErrorCode);
    }
}

#if defined(INCLUDE_FEATURE_VOLUME)
void OnSetVolumeSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnSetVolumeSink: Success!\n", ErrorCode );
    }
#endif

    if ( setvol_callback != NULL )
    {
        setvol_callback(ErrorCode);
    }
}

void OnSetMuteSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnSetMuteSink: Success!\n", ErrorCode );
    }
#endif

    if ( setmute_callback != NULL )
    {
        setmute_callback(ErrorCode);
    }
}
#endif

void OnSetPlayModeSink( struct AVRendererConnection * avrc, int ErrorCode, void * tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnSetPlayModeSink: Success!\n", ErrorCode );
    }
#endif

    if ( setplaymode_callback != NULL )
    {
        setplaymode_callback(ErrorCode);
    }
}

void OnGetMediaInfoSink( struct AVRendererConnection * avrc,int ErrorCode, int nrTracks, int mediaDuration, char * curUrI, char * nextURI,void * Tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnGetMediaInfoSink: Success!\n", ErrorCode );
        printf( "NrTracks = %d, MediaDuration = %d, CurUrl = %s, NextUrl = %s\n", nrTracks, mediaDuration, curUrI, nextURI );
    }
#endif

    if ( getmediainfo_callback != NULL )
    {
        getmediainfo_callback(ErrorCode, nrTracks, mediaDuration, curUrI, nextURI);
    }
}

void OnGetPositionSink(struct AVRendererConnection * avrc, int ErrorCode, int RelativeSeconds, int AbsoluteSeconds, int RelativeCounter, int AbsoluteCounter,void *Tag )
{
#if defined(_DEBUG) || defined(DEBUG)
    printf( "(%d) %s: ErrorCode:%d\n", __LINE__, __FUNCTION__, ErrorCode );
    if ( !ErrorCode )
    {
        printf( "OnGetPositionSink: Success!\n", ErrorCode );
        printf( "RelativeSeconds = %d, AbsoluteSeconds = %d, RelativeCounter = %d, AbsoluteCounter = %d\n", RelativeSeconds, AbsoluteSeconds, RelativeCounter, AbsoluteCounter );
    }
#endif

    if ( getposition_callback != NULL )
    {
        getposition_callback(ErrorCode, RelativeSeconds, AbsoluteSeconds, RelativeCounter, AbsoluteCounter);
    }
}

/************************************************************************/
/* Interface                                                            */
/************************************************************************/
struct _tDmrInfo * _getDmrInfo( char * udn )
{
    struct _tDmrInfo * ret_val = NULL;

    if ( NULL == udn )
        return NULL;

    if ( dmrinfos == NULL )
        return NULL;

    ILibHashTree_Lock( dmrinfos );
    ret_val = (struct _tDmrInfo *)ILibGetEntry(dmrinfos, (void *)udn, strlen(udn));
    ILibHashTree_UnLock( dmrinfos );

    return ret_val;
}

void PrintDmrList()
{
    char Key[128] = { 0 };
    int Len = 128, i = 0;
    struct _tDmrInfo * Val = NULL;
    void * dmr_enum = NULL;

    if ( dmrinfos == NULL ) return;
    ILibHashTree_Lock( dmrinfos );

    dmr_enum = ILibHashTree_GetEnumerator( dmrinfos );
    if ( dmr_enum == NULL ) return;
    while ( !ILibHashTree_MoveNext( dmr_enum ) )
    {
        ILibHashTree_GetValue( dmr_enum, (char **)&Key, &Len, ( ( void ** )( &Val ) ) );
        printf( "\t%d. %s [%s]\n", i++, ((struct AVRenderer*)(Val->render))->FriendlyName, ((struct AVRenderer*)(Val->render))->device->UDN );
    }
    ILibHashTree_DestroyEnumerator( dmr_enum );

    ILibHashTree_UnLock( dmrinfos );
}

char * GetDlnaDoc(char * udn)
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return NULL;
    }

    return RCP_GetDLNADOC( Val->render );
}

char * GetDlnaCap( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return NULL;
    }
    return RCP_GetDLNACAP( Val->render );
}

void GetDevCap( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    char * ret = NULL;
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_GetDeviceCap( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnGetDevCapSink );
}

int SupportPlayMode( char * udn, enum PlayModeEnum playmode )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return -1;
    }
    return RCP_SupportPlayMode( Val->render, playmode );
}

int SupportVolume( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return -1;
    }
    return RCP_SupportVolume( Val->render );
}

int SupportMute( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return -1;
    }
    return RCP_SupportMute( Val->render );
}

void Play( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_Play( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnPlaySink );
}

void Seek( char * udn, int pos )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_Seek( ((struct AVRenderer *)(Val->render))->Connection, pos, NULL, OnSeekSink );
}

void Stop( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_Stop( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnStopSink );
}

void Pause( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_Pause( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnPauseSink );
}

void Next( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_Next( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnNextSink );
}

void Prev( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_Prev( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnPrevSink );
}

void SetUri( char * udn, char * uri )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_SetUri( ((struct AVRenderer *)(Val->render))->Connection, uri, NULL, OnSetUriSink );
}

#if defined(INCLUDE_FEATURE_VOLUME)
void SetVolume( char * udn, int vol )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_SetVolume( ((struct AVRenderer *)(Val->render))->Connection, "Master", ( char )( vol ), NULL, OnSetVolumeSink );
}

void SetMute( char * udn, int ismute )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_SetMute( ((struct AVRenderer *)(Val->render))->Connection, "Master", ismute, NULL, OnSetMuteSink );
}
#endif

void SetPlayMode( char * udn, enum PlayModeEnum playmode )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_SetPlayMode( ((struct AVRenderer *)(Val->render))->Connection, playmode, NULL, OnSetPlayModeSink );
}

void GetMediaInfo( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_GetMediaInfo( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnGetMediaInfoSink );
}

void GetPosition( char * udn )
{
    struct _tDmrInfo * Val = _getDmrInfo( udn );
    if ( Val == NULL )
    {
        printf( "You choice a invalid device!\n" );
        return;
    }
    RCP_GetPosition( ((struct AVRenderer *)(Val->render))->Connection, NULL, OnGetPositionSink );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//static sem_t gsem;

void OnRenderStateChanged( struct AVRenderer * sender,struct AVRendererConnection * Connection )
{
    int i;
    //sem_wait( gsem );
    printf( "%s State changed                                       Begin\n", sender->FriendlyName );
    printf( "ProtocolInfo = %s\n", Connection->ProtocolInfo );
    printf( "MediaUri = %s\n", Connection->MediaUri );
    printf( "TrackUri = %s\n", Connection->TrackUri );
    printf( "TransportStatus = %s\n", Connection->TransportStatus );

    printf( "TotalTracks = %d\n", Connection->TotalTracks );
    printf( "TrackNumber = %d\n", Connection->TrackNumber );

    printf( "Play State = " );
    switch ( Connection->PlayState )
    {
    case AVRCP_PLAYING:
        printf( "AVRCP_PLAYING\n" );
        break;
    case AVRCP_STOPPED:
        printf( "AVRCP_STOPPED\n" );
        break;
    case AVRCP_PAUSED:
        printf( "AVRCP_PAUSED\n" );
        break;
    case AVRCP_RECORDING:
        printf( "AVRCP_RECORDING\n" );
        break;
    case AVRCP_TRANSITIONING:
        printf( "AVRCP_TRANSITIONING\n" );
        break;
    case AVRCP_NO_MEDIA:
        printf( "AVRCP_NO_MEDIA\n" );
        break;
    default:
        printf( "AVRCP_UNKNOWN\n" );
        break;
    }
    printf( "Play Mode = " );
    switch ( Connection->PlayMode )
    {
    case AVRCP_NORMAL:
        printf( "AVRCP_NORMAL\n" );
        break;
    case AVRCP_REPEAT_ALL:
        printf( "AVRCP_REPEAT_ALL\n" );
        break;
    case AVRCP_REPEAT_ONE:
        printf( "AVRCP_REPEAT_ONE\n" );
        break;
    case AVRCP_RANDOM:
        printf( "AVRCP_RANDOM\n" );
        break;
    case AVRCP_SHUFFLE:
        printf( "AVRCP_SHUFFLE\n" );
        break;
    case AVRCP_INTRO:
        printf( "AVRCP_INTRO\n" );
        break;
    default:
        printf( "AVRCP_INVALID\n" );
        break;
    }

    printf( "Duration = %d\n", Connection->Duration );

    printf( "TrackPosition = %s\n", Connection->TrackPosition );
    //struct CdsObject* TrackObject;

    for ( i = 0; i < Connection->SupportedRecordQualityModesLength; ++i )
    {
        printf( "SupportedRecordQualityModes[%d] = %s\n", i, Connection->SupportedRecordQualityModes[i] );
    }

    for ( i = 0; i < Connection->PlayMediaLength; ++i )
    {
        printf( "PlayMedia[%d] = %s\n", i, Connection->PlayMedia[i] );
    }

    for ( i = 0; i < Connection->RecordMediaLength; ++i )
    {
        printf( "RecordMedia[%d] = %s\n", i, Connection->RecordMedia[i] );
    }

    for ( i = 0; i < Connection->ChannelCount; ++i )
    {
        printf( "Channel[%d] = %s\n", i, Connection->Channel[i] );
    }

    printf( "Volume = %d\n", Connection->Volume[0] );
    printf( "Mute = %d\n", *( Connection->Mute ) );

    printf( "%s State changed                                       End\n", sender->FriendlyName );

    //sem_post( gsem );
}

void OnAddMediaRenderer(void* mediaRendererToken, struct AVRenderer* mediaRenderer)
{
    struct _tDmrInfo * dmr = NULL;
    if ( !g_dmr_flag )
    {
        dmrinfos = ILibInitHashTree();
        //sem_init( gsem );
        g_dmr_flag++;
    }

    dmr = ( struct _tDmrInfo * )malloc( sizeof( struct _tDmrInfo ) );

    if ( dmr == NULL )
    {
        fprintf(stderr, "malloc dmrinfo fail!\n");
        return;
    }

    dmr->dmr_token = mediaRendererToken;
    dmr->render = mediaRenderer;
    mediaRenderer->StateChanged = OnRenderStateChanged;

    ILibAddEntry( dmrinfos, mediaRenderer->device->UDN, strlen( mediaRenderer->device->UDN ), ( void * )dmr );
    printf( "Add AVRender %s[%s]\n", mediaRenderer->FriendlyName, mediaRenderer->device->UDN );
    if ( avrender_add != NULL )
    {
        avrender_add(mediaRenderer->device->UDN, mediaRenderer->device->FriendlyName);
    }
}

void OnRemoveMediaRenderer(void* mediaRendererToken, struct AVRenderer* mediaRenderer)
{
    void * dmrinfo;

    if ( !dmrinfos ) return;
    dmrinfo = ILibGetEntry( dmrinfos, mediaRenderer->device->UDN, strlen( mediaRenderer->device->UDN ) );
    ILibDeleteEntry( dmrinfos, mediaRenderer->device->UDN, strlen( mediaRenderer->device->UDN ) );
    free( dmrinfo );

    if ( !( --g_dmr_flag ) )
    {
        ILibDestroyHashTree( dmrinfos );
        dmrinfos = NULL;
    }
    printf( "Remove AVRender %s[%s]...\n", mediaRenderer->FriendlyName, mediaRenderer->device->UDN );
    if ( avrender_del != NULL )
    {
        avrender_del(mediaRenderer->device->UDN, mediaRenderer->device->FriendlyName);
    }
}

/* thread pool add */
#if defined(_POSIX)
void* pool_thread(void *args)
{
    ILibThreadPool_AddThread(args);
    return (0);
}
#else
DWORD WINAPI pool_thread(void *args)
{
    ILibThreadPool_AddThread(args);
    return (0);
}
#endif

AVRHandle createAVRCP(int threadpool_size)
{
    int count;
#if defined(_POSIX)
    struct sigaction setup_action;
    sigset_t block_mask;
    pthread_t t, cmdloopthread;
#else
    DWORD ptid = 0;
    DWORD ptid2 = 0;
#endif

    struct _tMAVRCP * p_mavrcp = (struct _tMAVRCP *)malloc(sizeof(struct _tMAVRCP));
    memset(p_mavrcp, 0, sizeof(struct _tMAVRCP));
    sem_init(p_mavrcp->mavrcp_lock, 0, 1);
    p_mavrcp->mavrcp_dmr_tables = ILibInitHashTree();

    p_mavrcp->mavrcp_stackchain = ILibCreateChain();
    p_mavrcp->mavrcp_threadpool = ILibThreadPool_Create();

    for( count = 0; count < threadpool_size; ++count )
    {
#if defined(_POSIX)
        pthread_create(&t,NULL,&pool_thread,p_mavrcp->mavrcp_threadpool);
#else
        ::CreateThread(NULL,0,&pool_thread,p_mavrcp->mavrcp_threadpool,0,&ptid);
#endif
    }

    p_mavrcp->mavrcp_rendercp = CreateRendererCP(p_mavrcp->mavrcp_stackchain);

    RendererAdded = &OnAddMediaRenderer;
    RendererRemoved = &OnRemoveMediaRenderer;

    return (AVRHandle)(p_mavrcp);
}

int startAVRCP(AVRHandle avhandle)
{
    struct _tMAVRCP * p_mavrcp = (struct _tMAVRCP *)avhandle;
    if (avhandle == NULL) return -1;
    ILibStartChain(p_mavrcp->mavrcp_stackchain);
}

void stopAVRCP(AVRHandle avhandle)
{
    struct _tMAVRCP * p_mavrcp = (struct _tMAVRCP *)avhandle;
    if (avhandle == NULL) return;
    ILibStopChain(p_mavrcp->mavrcp_stackchain);
}

void destoryAVRCP(AVRHandle avhandle)
{
    struct _tMAVRCP * p_mavrcp = (struct _tMAVRCP *)avhandle;
    if (avhandle == NULL) return;
    sem_destroy(p_mavrcp->mavrcp_lock);
    ILibDestroyHashTree( p_mavrcp->mavrcp_dmr_tables );

    free(p_mavrcp);
}