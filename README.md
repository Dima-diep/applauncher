# applauncher

## What is it
This is simple menu for starting apps manually

## Usage
Create `app.conf` and `run.conf`

Text of `app.conf` is name of your apps in one line:
```
Firefox
Telegram
Metasploit Framework
```
`run.conf` is list of Linux commands for starting:
```
firefox
telegram-desktop
msfconsole
```
You cant use multi-line commands or names for apps.

## Building
1.Install ncurses and C compiler (gcc, clang)
```
  ~ $ apt install libncurses-dev gcc clang
```
2.Build it!
```
 ~ $ gcc applauncher.cpp -lncurses -o applauncher
```

On Termux/Android, fix this code line:
```
namespace file = std::filesystem;
```
to:
```
namespace file = std::__fs::filesystem;
```
