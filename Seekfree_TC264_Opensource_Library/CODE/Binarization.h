#ifndef CODE_BINARIZATION_H_
#define CODE_BINARIZATION_H_

#include "SEEKFREE_MT9V03X.h"//Ϊ��Ҫuint8���ֶ���,��ֵ���㷨�е�ĳЩ��ѧ����,����ͷͼ���ȫ�ֱ���
//************ȫ�ֱ���**************
extern uint8 BinaryImage[MT9V03X_H][MT9V03X_W];
//**********************************


uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height);     //�����ֵ����ֵ: ���

void ImageBinary(void);                                             //������ֵ��ֵ��ͼ���޸�ԭ������




#endif /* CODE_BINARIZATION_H_ */