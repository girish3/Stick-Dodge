cmake_minimum_required(VERSION 3.24)
project(Stick_Dodge)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(include/SDL)
include_directories(include/SDL_ttf)
include_directories(include/SDL_image)
include_directories(include/SDL_mixer)
include_directories("templates node and linked list")

add_executable(Stick_Dodge
        include/SDL/begin_code.h
        include/SDL/close_code.h
        include/SDL/SDL.h
        include/SDL/SDL_active.h
        include/SDL/SDL_audio.h
        include/SDL/SDL_byteorder.h
        include/SDL/SDL_cdrom.h
        include/SDL/SDL_config.h
        include/SDL/SDL_copying.h
        include/SDL/SDL_cpuinfo.h
        include/SDL/SDL_endian.h
        include/SDL/SDL_error.h
        include/SDL/SDL_events.h
        include/SDL/SDL_getenv.h
        include/SDL/SDL_joystick.h
        include/SDL/SDL_keyboard.h
        include/SDL/SDL_keysym.h
        include/SDL/SDL_loadso.h
        include/SDL/SDL_main.h
        include/SDL/SDL_mouse.h
        include/SDL/SDL_mutex.h
        include/SDL/SDL_name.h
        include/SDL/SDL_opengl.h
        include/SDL/SDL_platform.h
        include/SDL/SDL_quit.h
        include/SDL/SDL_rwops.h
        include/SDL/SDL_stdinc.h
        include/SDL/SDL_syswm.h
        include/SDL/SDL_thread.h
        include/SDL/SDL_timer.h
        include/SDL/SDL_types.h
        include/SDL/SDL_version.h
        include/SDL/SDL_video.h
        include/SDL_ttf/SDL_ttf.h
        include/SDL_mixer/SDL_mixer.h
        include/SDL_image/SDL_image.h
        include/action.h
        include/const.h
        include/Game.h
        include/Goli.h
        include/LinkedList.h
        include/Menu.h
        include/MenuItem.h
        include/Node.h
        include/Stage.h
        include/timer.h
        src/action.cpp
        src/Game.cpp
        src/Goli.cpp
        src/LinkedList.cpp
        src/Menu.cpp
        src/MenuItem.cpp
        src/Node.cpp
        src/Stage.cpp
        src/timer.cpp
        "templates node and linked list/LinkedList.cpp"
        "templates node and linked list/LinkedList.h"
        "templates node and linked list/Node.cpp"
        "templates node and linked list/Node.h")
