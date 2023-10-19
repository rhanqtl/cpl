set(SRCS
    Node.cpp
    Visitor.cpp
)

set(LIB_NAME cpl_ast)
add_library(${LIB_NAME} STATIC)
target_sources(${LIB_NAME} PRIVATE ${SRCS})
