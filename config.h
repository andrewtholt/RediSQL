
struct config {
    int     daemonize;      // 1=yes
    char   *pidfile;        // /var/run/redis.pid
    int     port;           // 6379
    int     timeout;        // 0
    int tcp_keepalive;      // 0
    char loglevel[32];         // notice
    int syslog_enabled;     // 0=no
    char syslog_ident[32];     // redis
    char *syslog_facility;  // local0
    int databases;         // 16
    //    save 900 1
    //    save 300 10
    //    save 60 10000
    int stop_writes_on_bgsave_error; // 1=yes
    int rdbcompression;             //  1=yes
    int rdbchecksum;                //  yes
    char dbfilename[32];               // dump.rdb
    char dir[255];                       // /var/redis_6379
    int slave_serve_stale_data;     // 1=yes
    int slave_read_only;            // 1=yes
    int repl_disable_tcp_nodelay;    // no
    int slave_priority;             // 100
    int appendonly;              //  no
    char appendfsync[32];       // everysec
    int no_appendfsync_on_rewrite;  // no
    int auto_aof_rewrite_percentage;    // 100
    int auto_aof_rewrite_min_size;  //  64mb
    //        lua_time_limit 5000
    int slowlog_log_slower_than;    // 10000
    int  slowlog_max_len;   //  128
    int  hash_max_ziplist_entries;  // 512
    int  hash_max_ziplist_value;    // 64
    int  list_max_ziplist_entries;  // 512
    int  list_max_ziplist_value;    // 64
    int  set_max_intset_entries;    // 512
    int  zset_max_ziplist_entries;  // 128
    int  zset_max_ziplist_value;    // 64
    int  activerehashing;           // yes
    //        int  client_output_buffer_limit normal 0 0 0
    //        int  client_output_buffer_limit slave 256mb 64mb 60
    //        int  client_output_buffer_limit pubsub 32mb 8mb 60
    int  hz;    //  10
};

