cmake_minimum_required(VERSION 3.10)
project(SWEA_B_Problem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(solution SWEA_B/26113/main.cpp SWEA_B/26113/solution.cpp)

if(NOT MSVC)
    target_compile_options(solution PRIVATE 
        -Wall           # 모든 기본 경고 활성화
        -Wextra         # 추가적인 경고 활성화
        -Wpedantic      # ISO C++ 표준을 엄격히 따름 (표준 외 문법 에러 유도)
        # -Werror         # 모든 경고를 '에러'로 취급 (실수 방지)
        -O3             # SWEA 실전 최적화
    )
    target_link_options(solution PRIVATE "-Wl,--stack,268435456")
endif()