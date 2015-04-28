#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#define KEYSTREAM_SIZE 256
#define KEY_SIZE 16

int cunfair_rc4_keystream(char *key, unsigned char *keystream_buffer) {
  // our rc4 array
  unsigned char s[256];
  // our index for iterating across the internal state
  unsigned int i = 0;
  // our 2nd index, used for scheduling and keystream generation
  unsigned char j = 0;
  // our index for keystream generation
  unsigned int i2 = 0;
  // our buffer for swapping s[i] and s[j]
  unsigned char swap_buffer = 0;

  // init rc4 array
  s[0]=0;s[1]=1;s[2]=2;s[3]=3;s[4]=4;s[5]=5;s[6]=6;s[7]=7;s[8]=8;s[9]=9;s[10]=10;s[11]=11;s[12]=12;s[13]=13;s[14]=14;s[15]=15;s[16]=16;s[17]=17;s[18]=18;s[19]=19;s[20]=20;s[21]=21;s[22]=22;s[23]=23;s[24]=24;s[25]=25;s[26]=26;s[27]=27;s[28]=28;s[29]=29;s[30]=30;s[31]=31;s[32]=32;s[33]=33;s[34]=34;s[35]=35;s[36]=36;s[37]=37;s[38]=38;s[39]=39;s[40]=40;s[41]=41;s[42]=42;s[43]=43;s[44]=44;s[45]=45;s[46]=46;s[47]=47;s[48]=48;s[49]=49;s[50]=50;s[51]=51;s[52]=52;s[53]=53;s[54]=54;s[55]=55;s[56]=56;s[57]=57;s[58]=58;s[59]=59;s[60]=60;s[61]=61;s[62]=62;s[63]=63;s[64]=64;s[65]=65;s[66]=66;s[67]=67;s[68]=68;s[69]=69;s[70]=70;s[71]=71;s[72]=72;s[73]=73;s[74]=74;s[75]=75;s[76]=76;s[77]=77;s[78]=78;s[79]=79;s[80]=80;s[81]=81;s[82]=82;s[83]=83;s[84]=84;s[85]=85;s[86]=86;s[87]=87;s[88]=88;s[89]=89;s[90]=90;s[91]=91;s[92]=92;s[93]=93;s[94]=94;s[95]=95;s[96]=96;s[97]=97;s[98]=98;s[99]=99;s[100]=100;s[101]=101;s[102]=102;s[103]=103;s[104]=104;s[105]=105;s[106]=106;s[107]=107;s[108]=108;s[109]=109;s[110]=110;s[111]=111;s[112]=112;s[113]=113;s[114]=114;s[115]=115;s[116]=116;s[117]=117;s[118]=118;s[119]=119;s[120]=120;s[121]=121;s[122]=122;s[123]=123;s[124]=124;s[125]=125;s[126]=126;s[127]=127;s[128]=128;s[129]=129;s[130]=130;s[131]=131;s[132]=132;s[133]=133;s[134]=134;s[135]=135;s[136]=136;s[137]=137;s[138]=138;s[139]=139;s[140]=140;s[141]=141;s[142]=142;s[143]=143;s[144]=144;s[145]=145;s[146]=146;s[147]=147;s[148]=148;s[149]=149;s[150]=150;s[151]=151;s[152]=152;s[153]=153;s[154]=154;s[155]=155;s[156]=156;s[157]=157;s[158]=158;s[159]=159;s[160]=160;s[161]=161;s[162]=162;s[163]=163;s[164]=164;s[165]=165;s[166]=166;s[167]=167;s[168]=168;s[169]=169;s[170]=170;s[171]=171;s[172]=172;s[173]=173;s[174]=174;s[175]=175;s[176]=176;s[177]=177;s[178]=178;s[179]=179;s[180]=180;s[181]=181;s[182]=182;s[183]=183;s[184]=184;s[185]=185;s[186]=186;s[187]=187;s[188]=188;s[189]=189;s[190]=190;s[191]=191;s[192]=192;s[193]=193;s[194]=194;s[195]=195;s[196]=196;s[197]=197;s[198]=198;s[199]=199;s[200]=200;s[201]=201;s[202]=202;s[203]=203;s[204]=204;s[205]=205;s[206]=206;s[207]=207;s[208]=208;s[209]=209;s[210]=210;s[211]=211;s[212]=212;s[213]=213;s[214]=214;s[215]=215;s[216]=216;s[217]=217;s[218]=218;s[219]=219;s[220]=220;s[221]=221;s[222]=222;s[223]=223;s[224]=224;s[225]=225;s[226]=226;s[227]=227;s[228]=228;s[229]=229;s[230]=230;s[231]=231;s[232]=232;s[233]=233;s[234]=234;s[235]=235;s[236]=236;s[237]=237;s[238]=238;s[239]=239;s[240]=240;s[241]=241;s[242]=242;s[243]=243;s[244]=244;s[245]=245;s[246]=246;s[247]=247;s[248]=248;s[249]=249;s[250]=250;s[251]=251;s[252]=252;s[253]=253;s[254]=254;s[255]=255;

  // key scheduling
  // shuffle rc4 array, 16 byte (128 bit) key
  for (i = j = 0; i < 256; i++) {
    // calculate j
    j = (j + s[i] + key[i%KEY_SIZE]) % 256;

    // swap s[i] and s[j]
    swap_buffer = s[i];
    s[i] = s[j];
    s[j] = swap_buffer;
  }

  // keystream generation
  for (i2 = i = j = 0; i2 < KEYSTREAM_SIZE; i2++) {
    // calculate i and j
    i = (i+1) % 256;
    j = (j+s[i]) % 256;

    // swap s[i] and s[j]
    swap_buffer = s[i];
    s[i] = s[j];
    s[j] = swap_buffer;

    // save value of keystream
    keystream_buffer[i2] = s[(s[i] + s[j]) % 256];
  }
  
  return 0;
}

int cunfair_get_random_data(char *random_data, size_t data_size) {
  int fd = -1;

  if (-1 == (fd = open("/dev/urandom", O_RDONLY))) {
    abort();
  }


  if (-1 == read(fd, random_data, data_size)) {
    abort();
  }

  return 0;
}

int cunfair_rc4_gen (int num_samples) {
  unsigned char keystream_buffer[KEYSTREAM_SIZE];
  char *key = NULL;
  char *random_data = NULL;
  int i = 0;

  if (NULL == (random_data = malloc(num_samples*KEY_SIZE))) {
    abort();
  }

  // get all our random data
  cunfair_get_random_data(random_data, num_samples*KEY_SIZE);
  key = random_data;
  for (i = 0; i < num_samples; i++) {
    cunfair_rc4_keystream(key, keystream_buffer);
    key += KEY_SIZE;

    /* print out our keystream
    fprintf(stderr, "keystream[%.4i]: ", i);
    int j = 0;
    for (j = 0; j < KEYSTREAM_SIZE; j++) {
      fprintf(stderr, "%02X", keystream_buffer[j]);
    }
    fprintf(stderr, "\n");
    // */
  
    // count occurances
  }

  return 0;
}

void *wrap_cunfair_rc4_gen (void *arg) {
  cunfair_rc4_gen(*(int *)arg);

  return NULL;
}

void cunfair_print_usage (char *name) {
  fprintf(stderr, "usage: %s [num_samples]\n", name);
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "error: invalid number of arguments\n");
    cunfair_print_usage(argv[0]);
    abort();
  }

  int num_samples = -1;
  int num_cpu = sysconf(_SC_NPROCESSORS_ONLN);
  pthread_t childs[num_cpu];

  num_samples = atoi(argv[1]);

  fprintf(stdout, "num_samples: %.4i\n", num_samples);
  num_samples = num_samples/num_cpu;

  for (int i = 0; i < num_cpu; i++) {
    pthread_create(&childs[i], NULL, wrap_cunfair_rc4_gen, &num_samples);
  }
  for (int i = 0; i < num_cpu; i++) {
    pthread_join(childs[i], NULL);
  }

  //return cunfair_rc4_gen(num_samples);
  return 0;
}
