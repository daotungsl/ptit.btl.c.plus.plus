#include "auth.h"
#include "login.h"
#include "register.h"
#include "../entities/User.h"

User handleLogin() {
    return login();
}

void handleRegister() {
    registerUser();
}
