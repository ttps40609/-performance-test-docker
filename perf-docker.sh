while :
do
_date=$(date +%Y/%m/%d)
_time=$(date +%H:%M:%S)
_hostname=$(hostname)
_cpu1m=$(uptime | grep -ohe 'load average[s:][: ].*' | awk '{ print $3}'|cut -d ',' -f 1)
_cpu5m=$(uptime | grep -ohe 'load average[s:][: ].*' | awk '{ print $4}'|cut -d ',' -f 1)
_cpu15m=$(uptime | grep -ohe 'load average[s:][: ].*' | awk '{ print $5}')
_network=$(iperf3 -c 20.0.0.2 -p $PORT -t 1|sed -n '8p' | awk '{printf $7}')
_ip=$(ifconfig |sed -n '2p'|awk '{printf $2}'|cut -d ':' -f2)

_sql=\'$_date\',\'$_time\',\'$_hostname\',\'$_cpu1m\',\'$_cpu5m\',\'$_cpu15m\',\'$_network\',\'$_ip\',\'$CONTAINERS\'
echo $_sql
mysql --login-path=dbname << EOF
use perf;
INSERT INTO
docker(Date,Time,Hostname,Cpu1m,Cpu5m,Cpu15m,Network_bandwitch,Ip,containers)
VALUES($_sql)
EOF
sleep 4
done
