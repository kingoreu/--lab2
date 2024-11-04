# 컴파일러와 옵션
CC = gcc
CFLAGS = -Wall -fPIC

# 디렉토리 설정
LIBDIR = lib
SRCS = solution1_main.c calc.c
OBJS = $(SRCS:.c=.o)

# 동적 파일을 위한 새로운 소스 파일
DYNAMIC_SRCS = main_dynamic.c
DYNAMIC_OBJS = $(DYNAMIC_SRCS:.c=.o)

# 타겟
STATIC_LIB = $(LIBDIR)/libcalc.a
SHARED_LIB = $(LIBDIR)/libcalc.so
EXEC_STATIC = main_static
EXEC_SHARED = main_shared
EXEC_DYNAMIC = main_dynamic

# 모든 타겟 빌드
all: $(STATIC_LIB) $(SHARED_LIB) $(EXEC_STATIC) $(EXEC_SHARED) $(EXEC_DYNAMIC)

# 정적 라이브러리 생성
$(STATIC_LIB): calc.o | $(LIBDIR)
	ar rcs $@ calc.o

# 공유 라이브러리 생성
$(SHARED_LIB): calc.o | $(LIBDIR)
	$(CC) -shared -o $@ calc.o

# 실행 파일 생성 (정적 링크)
$(EXEC_STATIC): solution1_main.o $(STATIC_LIB)
	$(CC) -o $@ solution1_main.o -L$(LIBDIR) -lcalc

# 실행 파일 생성 (공유 링크)
$(EXEC_SHARED): solution1_main.o $(SHARED_LIB)
	$(CC) -o $@ solution1_main.o -L$(LIBDIR) -lcalc

# 실행 파일 생성 (동적 링크)
$(EXEC_DYNAMIC): $(DYNAMIC_OBJS) $(SHARED_LIB)
	$(CC) -o $@ $(DYNAMIC_OBJS) -L$(LIBDIR) -lcalc

# 목적 파일 생성 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 동적 목적 파일 생성 규칙
$(DYNAMIC_OBJS): $(DYNAMIC_SRCS)

# lib 디렉토리 생성
$(LIBDIR):
	mkdir -p $(LIBDIR)

# 정리
clean:
	rm -f *.o $(LIBDIR)/*.a $(LIBDIR)/*.so $(EXEC_STATIC) $(EXEC_SHARED) $(EXEC_DYNAMIC)

.PHONY: all clean

