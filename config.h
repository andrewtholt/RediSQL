struc config {
    int     daemonize;      // 1=yes
    char   *pidfile;        // /var/run/redis.pid
    int     port;           // 6379
    int     timeout;        // 0
    int tcp-keepalive;      // 0
    char *loglevel;         // notice
    int syslog-enabled;     // 0=no
    char *syslog-ident;     // redis
    char *syslog-facility;  // local0
    inst databases;         // 16
//    save 900 1
//    save 300 10
//    save 60 10000
    int stop-writes-on-bgsave-error; // 1=yes
    int rdbcompression;             //  1=yes
    int rdbchecksum;                //  yes
    char *dbfilename;               // dump.rdb
    char *dir                       // /var/redis_6379
    slave-serve-stale-data yes
    slave-read-only yes
    repl-disable-tcp-nodelay no
    slave-priority 100
    appendonly no
    appendfsync everysec
    no-appendfsync-on-rewrite no
    auto-aof-rewrite-percentage 100
    auto-aof-rewrite-min-size 64mb
    lua-time-limit 5000
    slowlog-log-slower-than 10000
    slowlog-max-len 128
    hash-max-ziplist-entries 512
    hash-max-ziplist-value 64
    list-max-ziplist-entries 512
    list-max-ziplist-value 64
    set-max-intset-entries 512
    zset-max-ziplist-entries 128
    zset-max-ziplist-value 64
    activerehashing yes
    client-output-buffer-limit normal 0 0 0
    client-output-buffer-limit slave 256mb 64mb 60
    client-output-buffer-limit pubsub 32mb 8mb 60
    hz 10
}
