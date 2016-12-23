# performance-test-docker
# 前言
這將會將系統的付載一路到100％
並將其「Date」,「Time」,「Hostname」,「Cpu1m」,「Cpu5m」,「Cpu15m」,「Bandwitch」,「Containers」回傳至Mysql的資料庫中
# 使用方法
因為我將登入SQL與回傳SQL的指令打在BASH指令中
為了安全我使用mysql_config_editor這套件進行登入
### 1.寫入MySql登入資訊
```
sudo mysql_config_editor set --login-path=dbname --host=127.0.0.1 --user=root --password
```
* --login-path :  登入資訊名稱
* --host : 需要登入的伺服器位置
* --user : 使用者帳號
* --password : 使用密碼登入（不需要在此打入資訊,他會自動跳出輸入訊息）

### 2.執行程式
```
sudo sh start.sh
```
# 資料來源
perf.c -- [研究所學習筆記](http://blog.xuite.net/ian11832/blogg/30774340-+在linux上增加CPU想要的負載值程式)

mysql_config_editor -- [Mr. 沙先生](https://shazi.info/mysql-執行-bash-script-出現-warning-using-a-password-on-the-command-line-interface-can-be-insecure/)
