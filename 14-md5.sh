#!/bin/bash


# seed is 1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZกขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรลวศษสหฬอฮ with 194 byte


cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed

cat seed seed > tmp
mv tmp seed
# at this point it's 3gb

# 2147483648 % 194 = 66  1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZก = 65 cut 1 byte
head -c 2147483647 seed > tmp 
md5 tmp