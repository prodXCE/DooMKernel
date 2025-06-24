void kmain(void) {
  volatile unsigned short *video_memory = (unsigned short *)0xB8000;

  const char *message = "Welcome to DooM Kernel";

  for (int i = 0; message[i] != '\0'; ++i) {
      video_memory[i] = (0x0F00) | message[i];
  }

  return;


}

