unsigned int infExpected[][4] = {

  { 0x1, 0x3ff, 0x00000, 0x00000000 },

  { 0x0, 0x000, 0x00000, 0x00000000 },

  { 0x0, 0x3ff, 0x00000, 0x00000000 },

  { 0x1, 0x400, 0x8cccc, 0xcccccccd },

  { 0x1, 0x400, 0x26666, 0x66666666 },

  { 0x1, 0x401, 0x00000, 0x00000000 },

  { 0x0, 0x000, 0x00000, 0x00000000 },

  { 0x0, 0x400, 0x00000, 0x00000000 },

#if defined(FILIB_EXTENDED)
  { 0x0, 0x7ff, 0x80000, 0x00000000 },

  { 0x1, 0x7ff, 0x00000, 0x00000000 },

  { 0x1, 0x7ff, 0x00000, 0x00000000 },

  { 0x0, 0x7fe, 0xfffff, 0xffffffff },

  { 0x1, 0x7ff, 0x00000, 0x00000000 },

  { 0x1, 0x7ff, 0x00000, 0x00000000 },

  { 0x1, 0x7ff, 0x00000, 0x00000000 },

  { 0x1, 0x3ff, 0x00000, 0x00000000 },

  { 0x0, 0x000, 0x00000, 0x00000000 },

  { 0x0, 0x3ff, 0x00000, 0x00000000 },

  { 0x1, 0x7fe, 0xfffff, 0xffffffff },

  { 0x0, 0x7fe, 0xfffff, 0xffffffff },

  { 0x1, 0x7fe, 0xfffff, 0xffffffff },

#endif
};



unsigned int supExpected[][4] = {

  { 0x1, 0x3ff, 0x00000, 0x00000000 },

  { 0x0, 0x000, 0x00000, 0x00000000 },

  { 0x0, 0x3ff, 0x00000, 0x00000000 },

  { 0x1, 0x400, 0x00000, 0x00000000 },

  { 0x0, 0x000, 0x00000, 0x00000000 },

  { 0x1, 0x3ff, 0x00000, 0x00000000 },

  { 0x0, 0x401, 0xacccc, 0xcccccccd },

  { 0x0, 0x401, 0x46666, 0x66666666 },

#if defined(FILIB_EXTENDED)
  { 0x0, 0x7ff, 0x80000, 0x00000000 },

  { 0x0, 0x7ff, 0x00000, 0x00000000 },

  { 0x1, 0x7fe, 0xfffff, 0xffffffff },

  { 0x0, 0x7ff, 0x00000, 0x00000000 },

  { 0x1, 0x3ff, 0x00000, 0x00000000 },

  { 0x0, 0x000, 0x00000, 0x00000000 },

  { 0x0, 0x3ff, 0x00000, 0x00000000 },

  { 0x0, 0x7ff, 0x00000, 0x00000000 },

  { 0x0, 0x7ff, 0x00000, 0x00000000 },

  { 0x0, 0x7ff, 0x00000, 0x00000000 },

  { 0x0, 0x7fe, 0xfffff, 0xffffffff },

  { 0x0, 0x7fe, 0xfffff, 0xffffffff },

  { 0x1, 0x7fe, 0xfffff, 0xffffffff },

#endif
};



