void assert(bool value, char* errorMsg);

void assert(bool val, char* msg) {
  if(!val) {
    printf("Test fail!\n\tassertion failed with message: '%s'\n", msg);
    exit(1);
  }
}
