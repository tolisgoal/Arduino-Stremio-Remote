import pyautogui
import pywintypes #needed to install win32gui in pyinstaller exe
import win32gui
import win32con
import serial

# playpause
# nexttrack
# prevtrack
# volumeup
# volumedown

arduinoPort = serial.Serial()

def findWindow(title): # find window by title 
    return win32gui.FindWindow(None, title)
    

def focusWindow(hwnd):
    try:
        if win32gui.IsIconic(hwnd): # Check if window is minimized
            win32gui.ShowWindow(hwnd, win32con.SW_RESTORE) # Bring window out of minimized form
        win32gui.SetForegroundWindow(hwnd)
    except:
        print("Could not find window...")
        #input() #was here for debugging purposes
        return() # if find window returns null # exit() if running via python and not executable

def cleanSerialData(data):
    cleanData = str(data).translate({"b'": '', '\r': '', '\n': ''})
    return cleanData

def main():
    #print(pyautogui.KEYBOARD_KEYS)

    hwnd = findWindow('Stremio - Freedom to Stream') # Set desired window here

    try:
        arduinoPort.baudrate=115200
        arduinoPort.port='COM3'
        arduinoPort.open()
    except:
        print('Please check the port')
        #input() #was here for debugging purposes
        return()
    
    while(1):
        data = arduinoPort.readline().decode('utf-8').rstrip()
        print(data)
        match(data):
            case '+':
                focusWindow(hwnd)
                pyautogui.hotkey('volumeup')
            case '-':
                focusWindow(hwnd)
                pyautogui.hotkey('volumedown')
            case '>>|':
                focusWindow(hwnd)
                pyautogui.hotkey('nexttrack')
            case '|<<':
                focusWindow(hwnd)
                pyautogui.hotkey('prevtrack')
            case '|> ||': # Using space here because stremio doesn't accept playpause hotkey
                focusWindow(hwnd)
                pyautogui.hotkey('space')
            case 'EQ':
                focusWindow(hwnd)
                pyautogui.hotkey('f11')
            case 'exit':
                print("Exiting...")
                arduinoPort.close()
                return()
            case _:
                print("Waiting...")


        #    focusWindow(findWindow('Stremio - Freedom to Stream'))
    

if __name__ == "__main__":
    main()