#include <android/binder_manager.h>
#include <android/binder_process.h>
int main(int, char**) {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

        return 1;
    }

    ABinderProcess_joinThreadPool();
    return 0;
}
