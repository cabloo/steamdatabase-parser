# Build configuration
DIR := build
SRC_DIR := src
LIB_DIR := lib
DEBUG := -g

# The Command Line Interface output file
CLI_OUTPUT := run

# Universal Includes
SRCS := \
    Service/Crawler/State.cpp Service/Crawler/Crawler.cpp \
    Service/Crawler/Queue/ItemQueue.cpp Service/Crawler/Queue/UserQueue.cpp \
    Service/Crawler/Queue/ApiKeyQueue.cpp \
	Service/Database/Database.cpp Service/Database/Dispatcher.cpp \
    Service/Database/MySQL/MySQLDispatcher.cpp \
    Service/Config/Config.cpp \
    Service/Api/Api.cpp Service/Api/Parser/TF2Parser.cpp \
    Service/Api/Parser/IEconItemsParser.cpp Service/Api/Parser/Dota2Parser.cpp \
    Util/String/String.cpp Util/Steam/Steam.cpp Util/Log/Log.cpp \

# Executables
EXEC_SRCS := Executable/Dashboard/Parser.cpp

# Libraries
LIB_SRCS := \
    jsoncpp.cpp\

# TODO: use a map
CLI_SRC := Executable/Dashboard/main.cpp
EXP_WKR_SRC := Executable/ExpiredWorker/main.cpp
QUEUE_WKR_SRC := Executable/QueueWorker/main.cpp
# End config

# Compile flags
CC := g++
LFLAGS := \
    -lmysqlcppconn \
    -Wl,-Bsymbolic-functions -Wl,-z,relro -lcurlpp -lstdc++ -lcurl \

CFLAGS := -I./$(SRC_DIR) -I./$(LIB_DIR) --std=c++11 -Wall $(DEBUG)
MFLAGS := -p./$(DIR)/

# Functions
OBJ_SUFFIX = .o
compile_src = $(addprefix $(DIR)/,$(call src_prefix,$(1:.cpp=$(OBJ_SUFFIX))))
compile_lib = $(addprefix $(DIR)/,$(call lib_prefix,$(1:.cpp=$(OBJ_SUFFIX))))
src_prefix = $(addprefix $(SRC_DIR)/,$(1))
lib_prefix = $(addprefix $(LIB_DIR)/,$(1))
depend = $(1:%.cpp=$(DIR)/$(SRC_DIR)/%.d)

# Config combinations
ALL_SRCS = $(SRCS) $(EXEC_SRCS)
CLI_OBJ = $(call compile_src,$(CLI_SRC))
EXP_OBJ = $(call compile_src,$(EXP_WKR_SRC))
QUEUE_OBJ = $(call compile_src,$(QUEUE_WKR_SRC))
EXEC_OBJS = $(call compile_src,$(EXEC_SRCS))
LIB_OBJS = $(call compile_lib,$(LIB_SRCS))

prod: OBJS = $(call compile_src,$(ALL_SRCS))
prod: lib $(call compile_src,$(ALL_SRCS)) workers cli

lib: $(LIB_OBJS)

exec: $(EXEC_OBJS) $(call exec,$(EXEC_PROGS))

cli: $(CLI_OBJ)
	$(CC) $(CFLAGS) $^ -o ./$(DIR)/$(CLI_OUTPUT) $(OBJS) $(LIB_OBJS) $(LFLAGS)

workers: queue_worker expired_worker

queue_worker: $(QUEUE_OBJ)
	$(CC) $(CFLAGS) $^ -o ./$(DIR)/queue_worker $(OBJS) $(LIB_OBJS) $(LFLAGS)

expired_worker: $(EXP_OBJ)
	$(CC) $(CFLAGS) $^ -o ./$(DIR)/expired_worker $(OBJS) $(LIB_OBJS) $(LFLAGS)

# Other
clean:
	rm -r ./$(DIR)/*

$(DIR)/%$(OBJ_SUFFIX): %.cpp
	@mkdir -p ./$(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR)/%.d: %.cpp
	@mkdir -p ./$(@D)
	@$(call make-depend,$<,$@)

# usage: $(call make-depend,source-file,depend-file)
define make-depend
  $(CC) -MM       \
        -MF $2    \
        -MP       \
        $(CFLAGS) \
        $1
endef

ifneq ($(MAKECMDGOALS),clean)
include $(call depend,$(ALL_SRCS))
endif
