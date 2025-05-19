@echo off
setlocal

REM Optional: Set path to g++ if needed
REM set PATH=C:\msys64\ucrt64\bin;%PATH%

echo Building wallet_manager.exe...
g++ -std=c++17 -Wall -Iinclude src/wallet_manager.cpp src/Card.cpp src/Wallet.cpp src/TransactionLogger.cpp -o bin/wallet_manager.exe
if errorlevel 1 (
    echo Failed to build wallet_manager.exe
    exit /b 1
)

echo Building remote_wallet.exe...
g++ -std=c++17 -Wall -Iinclude src/remote_wallet.cpp src/Card.cpp src/Wallet.cpp src/TransactionLogger.cpp -o bin/remote_wallet.exe
if errorlevel 1 (
    echo Failed to build remote_wallet.exe
    exit /b 1
)

echo Build successful.
exit /b 0
