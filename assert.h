void assert(bool value, char* errorMsg);

void assert(bool val, char* msg) {
  if(!val) {
    printf("assertion failed: %s\n", msg);
    exit(1);
  }
}
