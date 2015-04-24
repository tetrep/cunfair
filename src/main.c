#include <stdlib.h>

void print_usage(char *name) {
  fprint("usage: %s [num_samples] [keystream_length]\n");
}

int main (int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "error: invalid number of arguments\n");
    print_usage(argv[0]);
    abort();
  }

  int num_samples = -1;
  int keystream_length = -1;

  num_samples = atoi(argv[1]);
  keystream_length = atoi(argv[2]);

  fprintf(stdout, "num_samples : %i\nkeystream_length : %i\n", num_samples, keystream_length);

  return 0;
}
