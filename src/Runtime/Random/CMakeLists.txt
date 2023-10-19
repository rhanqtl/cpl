set(SRCS 
    Analysis/ConstraintPartition.cpp
    Analysis/SupportVarsCollector.cpp
)

set(LIB_NAME cpl_random)
add_library(${LIB_NAME} SHARED)
target_sources(${LIB_NAME} PRIVATE ${SRCS})
