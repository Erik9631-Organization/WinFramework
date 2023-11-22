set(udp udp/${platform}/UdpConnectionManager.cpp
        udp/${platform}/UdpConnectionManager.h)

source_group("src\\udp" FILES ${udp})

set(api
        api/ReceiverSubscriber.h
        api/ReceiverSubject.h)

source_group("src\\api" FILES ${api})

set(src
        ${platform}/Networking.h
        ${platform}/Networking.cpp)

source_group("src" FILES ${udp})

set(all_src ${udp}
            ${src}
            ${api})


add_library(${PROJECT_NAME} STATIC ${all_src})
target_include_directories(${PROJECT_NAME} PUBLIC
        udp/${platform}
        ${platform}
        api)