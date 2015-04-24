#include <stdio.h>
#include <stdlib.h>

int cunfair_rc4_keystream(int keystream_length, char *buffer) {
  return 0;
}

int cunfair_rc4_gen (int num_samples, int keystream_length) {
  int err = -1;
  char *buffer = NULL;

  // make buffer large enough to store the requested keystream size
  if (NULL == (buffer = malloc(keystream_length))) {
    fprintf(stderr, "error: Could not allocate memory for keystream; please download more RAM.\n");
    return -1;
  }

  if (-1 == (err = cunfair_rc4_keystream(keystream_length, buffer))) {
    fprintf(stderr, "error: Could not generator rc4 keystream of %i bytes.\n", keystream_length);
    return err;
  }

  return 0;
}

void cunfair_print_usage (char *name) {
  fprintf(stderr, "usage: %s [num_samples] [keystream_length]\n", name);
}

int main (int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "error: invalid number of arguments\n");
    cunfair_print_usage(argv[0]);
    abort();
  }

  int num_samples = -1;
  int keystream_length = -1;

  num_samples = atoi(argv[1]);
  keystream_length = atoi(argv[2]);

  fprintf(stdout, "num_samples : %i\nkeystream_length : %i\n", num_samples, keystream_length);

  return cunfair_rc4_gen(num_samples, keystream_length);
}
