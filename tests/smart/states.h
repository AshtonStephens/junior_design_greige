



#ifndef STATE_H_
#define STATE_H_

#define NUM_STATE_THREADS 8
#define THREAD_SIZE       10

#define THREAD_0 1 << 0
#define THREAD_1 1 << 1
#define THREAD_2 1 << 2
#define THREAD_3 1 << 3
#define THREAD_4 1 << 4
#define THREAD_5 1 << 5
#define THREAD_6 1 << 6
#define THREAD_7 1 << 7

int line_tracking (void *n)
{
    (void) n;
    std::cerr << "HI THIS WORKS" <<ste::endl;

}

// defines the structure to hold a single state
struct state {
    state () : action(NULL), data(NULL) {};
    state (int (*v)(void*), void*) : action(v), data(NULL) {};

    int (*action)(void*);
    void *data;
};

struct state_initializer {
    int threads;
    int id;
    state s;
};

state_initializer s = {THREAD_0 | THREAD_1,4,{line_tracking,NULL}};

#endif
