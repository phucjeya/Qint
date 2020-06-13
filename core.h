#pragma once

//Cell là 1 bytes ô nhớ, ở đồ án này Qint và Qfloat đều 16 bytes => 16 Cell trong RAM
#define MAX_CELL 16

//1 Cell có 8 bits
#define BITS_OF_CELL 8

//Phần trị Significant có 112 bits
#define NUM_OF_SIGNIFICANT_BITS 112

//Phần mũ có 15 bits
#define NUM_OF_EXPONENT_BITS 15

//Số quá K, và max của phần mũ
#define EXPONENT_BIAS 16383
#define MAX_EXPONENT 16383