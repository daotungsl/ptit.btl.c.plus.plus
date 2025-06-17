#include "auth.h"
#include "login.h"
#include "register.h"

UserRole handleLogin() {
    return login();
}

void handleRegister() {
    registerUser();
}
