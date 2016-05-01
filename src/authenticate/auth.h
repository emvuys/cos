#ifndef __AUTH_H__
#define __AUTH_H__

#define TAG_AUTH	0xDB
#define LENGTH_RES	8
#define LENGTH_CK	16
#define LENGTH_IK	16
#define LENGTH_KC	8

void initAuth(u1* ki, u1* opc);
u2 Auth(u1* rand, u1* authToken, u1* respBuf, u2* respLen);
void f1(u1* rand, u1* sqn, u1* amf, u1* xmaca);
void f1Star(u1* rand, u1* sqn, u1* amf, u1* xmaca);
void f1Internal(u1* rand, u1* sqn, u1* amf, u1* result);
void f2(u1* rand, u1* result);
void f3(u1* rand, u1* result);
void f4(u1* rand, u1* result);
void f5(u1* rand, u1* result);
void f5Star(u1* rand, u1* result);
 void f2345(u1* rand, u1* c, u1 r, u1* result);
 void rotate(u1 r, u1* s, u1* result);
 void xor(u1* a, u1* b, u1* out, u2 len);
 void convertC2(u1* res, u1* result);
 void convertC3(u1* ck, u1* ik, u1* result );
 void RijndaelKeySchedule(u1 key[16]);
 void KeyAdd(u1 state[4][4], u1 roundKeys[11][4][4], u4 round);
 u4 ByteSub(u1 state[4][4]);
 void ShiftRow(u1 state[4][4]);
 void MixColumn(u1 state[4][4]);
 void RijndaelEncrypt(u1 input[16], u1 output[16]);
 void aesTest(u1* key, u1* input, u1* output);
 


#endif
