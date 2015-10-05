ClientEngine::ClientSocketEngine()
{
    server = new SocketClass( error, message );
    buffer = new SocketClass::SocketBuffer( error );
    
    
}
int ClientEngine::ClientSocketEngine::packet( SocketClass* unused )
{
    switch ( server->bufferRecv.socketData.type )
    {
    case SM_SRV_POSUP:
        //MessageBox( NULL, TEXT("shouldnt see this"), NULL, 0 );
        break;
    case SM_SRV_POSUPALL:
        
        clientEngine->clientGameEngine( server->buffer.data );
        break;
    case SM_SRV_CREATEGAME:
        client_socket_server_create_game();
        break;
    case SM_SRV_JOINGAME:
        client_socket_server_join_game();
        break;
    case SM_SRV_REQUGAME:
         print("games:");
		 game_list_len = server->buf.data.gen.len;
		 game_list_offset = 0;
         for ( short a = 0; a < server->buf.data.gen.len; a++ )
         {
             print( "%i", server->buf.data.gen.int1[a] );
			 game_list[a] = server->buf.data.gen.int1[a];
         }
		 menu = MENU_SERVER_JOIN;
         break;
	case SM_SRV_VICTIM:
        client_socket_server_victim();
        break;
    case SM_SRV_CO:
        client_obj_recv_obj();
        break;
    }
    return 0;
}
int ClientEngine::ClientSocketEngine::sendControlState()
{
    buf->data.type = SM_CLI_CTRLCHANGE;
    buf->data.cc.marine_id = my_marine->id;
    buf->data.cc.game_id = game->id;
    
    buf->data.cc.input_data = my_marine->input_data;
    
    buf->len();
    buf->send_buf( server );
    return 0;
}
/*
int ClientEngine::ClientSocketEngine::send_position()
{
	buf->data.type = SM_CLI_POSUP;
	
	buf->data.gen.x = my_marine->body.x;
	buf->data.gen.q = my_marine->body.q;
	
	buf->data.gen.game_id = game->id;
	buf->data.gen.id = my_marine->id;
	
	buf->len();
    buf->send_buf( server );
    
	return 0;
}
*/
int ClientEngine::ClientSocketEngine::send_shot()
{
	Vector3 o = my_marine->body.x + my_marine->body.eye_offset;
	Vector3 v = my_marine->body.x;
	
	buf->data.type = SM_CLI_SENDSHOT;
	buf->data.gen.game_id = game->id;
	buf->data.gen.id = my_marine->id;
	
	buf->data.gen.v = v;
	buf->data.gen.r = o;
	
	buf->len();
    buf->send_buf( server );
    
	return 0;
}
int ClientEngine::ClientSocketEngine::server_create_game()
{
    client_game_create_game();
    
    game->id = server->buf.data.gen.game_id;
    
    my_marine = game->marines.at(0);
    
    prog_mode = PM_INGAME;
    input_mode = IM_FIRST;
    client_menu_core_update( MENU_NONE );
    print( "game %i created", game->id );
    
    return 0;
}
int ClientEngine::ClientSocketEngine::server_join_game()
{
    MARINE* m;
    
    client_game_create_game();
    
    game->id = server->buf.data.join.game_id;
    my_marine = game->marine( server->buf.data.join.my_id );
    
    for ( int a = 0; a < server->buf.data.join.len; a++ )
    {
        m = game->marine( server->buf.data.join.id[a] );
        m->health = server->buf.data.join.health[a];
    }
    
    prog_mode = PM_INGAME;
    input_mode = IM_FIRST;
    menu = MENU_NONE;
    
    print( "joined game %i. assigned to id %i", game->id, my_marine->id );
    
    return 0;
}
int ClientEngine::ClientSocketEngine::server_victim()
{
    MARINE* m = game->marine( server->buf.data.gen.id );
    print( "hit %i", m->id );
    if ( prog_mode == PM_INGAME )
    {
        try
        {
            m->health -= DAMAGE;
        }
        catch ( std::exception &e )
        {
            MessageBox( NULL, NULL, NULL, 0 );
        }
        if ( m == my_marine )
        {
            if ( my_marine->health <= 0 )
            {
                print("you were killed");
                
                delete game;
                game = NULL;
                my_marine = NULL;
                
                prog_mode = PM_MAINMENU;
                client_menu_core_update( MENU_SERVER_HOME );
            }
        }
    }
    return 0;
}
int ClientEngine::ClientSocketEngine::error( SOCKET_CLASS<OBJECT,SOCKET_DATA>* unused, int error )
{
    return 0;
}
int ClientEngine::ClientSocketEngine::disconnect()
{
    buf->data.type = SM_CLI_DISCONNECT;
    buf->len();
    buf->send_buf( server );
    
    server->s = INVALID_SOCKET;
    
    return 0;
}
int ClientEngine::ClientSocketEngine::connect( short PortNo, char* IPAddress )
{
	//Start up Winsock
    WSADATA wsadata;
    int error = WSAStartup(0x0202, &wsadata);
    if (error)
    {
        return FR_FAILURE;
    }
    //Did we get the right Winsock version?
    if (wsadata.wVersion != 0x0202)
    {
        return FR_FAILURE;
    }
    
    unsigned long inaddr = inet_addr (IPAddress);
    if ( inaddr == INADDR_NONE )
    {
        print("invalid ip");
        WSACleanup(); //Clean up Winsock
        return FR_FAILURE;
    }
    
    //Fill out the information needed to initialize a socket
    SOCKADDR_IN target; //Socket address information
    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inaddr;
    server->s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if ( server->s == INVALID_SOCKET )
    {
        return FR_FAILURE; //Couldn't create the socket
    }
    
    // Non-blocking
    u_long iMode=1;
	ioctlsocket( server->s, FIONBIO, &iMode );
    // try connecting...
    int result;
    
    fd_set fdset;
    fdset.fd_array[0] = server->s;
    fdset.fd_count = 1;
    
    timeval t;
    t.tv_sec = (long)TIMEOUT_SEC;
    t.tv_usec = (long)TIMEOUT_USEC;
    const timeval *tc = &t;
    print("attempting connect...");
    result=connect( server->s, (SOCKADDR *)&target, sizeof(target) );
    result=select(0,&fdset,NULL,NULL,tc);
    if (result == 0)
    {
       print("timeout");
       return FR_FAILURE;
    }
    else if (result == SOCKET_ERROR)
    {
        print("error");
		return FR_FAILURE;
    }
    else
    {
        print("connected to server");
        return FR_SUCCESS;
    }
}
int ClientEngine::ClientSocketEngine::recv_objective()
{
    OBJECTIVE<MARINE> * o = new OBJECTIVE<MARINE>;
    
	(*o) = server->buf.data.co.data;

    MARINE* creator = game->marine( server->buf.data.co.creator_id );
    MARINE* lower   = game->marine( server->buf.data.co.lower_id );
    
    objective_create( o, creator, lower, game );
    
    print("new objective received");
    
    return 0;
}
int ClientEngine::ClientSocketEngine::request_games()
{
    buf->data.type = SM_CLI_REQUGAME;
    buf->len();
    buf->send_buf( server );
    return 0;
}
int ClientEngine::ClientSocketEngine::attempt_join_game( int a )
{
	a += 10*game_list_offset;
	if ( game_list_len > a )
	{
		print("joining game %i ...", game_list[a]);
		client_join_join_game(game_list[a]);
	}
	return 0;
}
int ClientEngine::ClientSocketEngine::join_game( int int1 )
{
    buf->data.type = SM_CLI_JOINGAME;
    buf->data.gen.game_id = int1;
    buf->len();
    buf->send_buf( server );
    return 0;
}
