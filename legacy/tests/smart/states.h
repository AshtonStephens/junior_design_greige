

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
    std::cerr << "HI THIS WORKS" <<std::endl;
    return 0;
}

int default_state (void *v)
{
    (void) v;
    long long timer = millis();
    Serial.println("RUNTIME LOGIC ERROR - IN STATE THAT DOES NOT EXIST");
    while (100 > millis() - timer) {}
    exit(0);
    return 0;
}

// defines the structure to hold a single state
struct state 
{
    // ways to call
    state () : action(NULL), data(NULL) {};
    state (int (*f)(void*)) : action(f), data(NULL) {};
    state (int (*f)(void*), void*v) : action(f), data(v) {};

    // stored data
    int (*action)(void*);
    void *data;
};

struct state_initializer {
    int threads;
    int id;
    state s;
};

// takes in the state initializer array and
// places the relavent states into the thread;
template <int N>
void initialize_thread 
    (state_initializer (&si)[N], int routine, 
     state thread[THREAD_SIZE]) 
{
    int mask = 1 << routine;
    
    // setup state thread to be default
    for (int i = 0; i < THREAD_SIZE; ++i) thread[i] = {default_state};

    for (int i = 0; i < N; ++i) {
        if (!(si[i].threads & mask)) break; // leave if this thread not apply

        if (si[i].id > THREAD_SIZE) {
            Serial.println("FATAL INIT ERROR - STATE ID OUT OF BOUNDS");
        } else if (si[i].id <= 0) {
            Serial.println("FATAL INIT ERROR - STATE ID 0 OR LOWER IS INVALID");
        } else {
            thread[si[i].id] = si[i].s;
        }
    }
}

#endif
