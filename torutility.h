/* Copyright (c) 2019, Md Kawser Munshi
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the names of the copyright owners nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef TORUTILITY_H
#define TORUTILITY_H

#ifdef QT_CORE_LIB

#include <QByteArray>

#else

typedef signed char qint8
typedef unsigned char quint8

typedef signed int qint32
typedef unsigned int quint32
typedef signed long qint64
typedef unsigned long quint64

#endif


namespace torutility {


qint32 getBase32EncodedLength(qint32 bytes);
qint32 getBase32DecodedLength(qint32 bytes);

std::string toBase32(const std::string &data, bool &success);
std::string fromBase32(const std::string &data, bool &success);

std::string toBase32(const std::string &data);
std::string fromBase32(const std::string &data);


#ifdef QT_CORE_LIB

QByteArray toBase32(const QByteArray &data, bool &success);
QByteArray fromBase32(const QByteArray &data, bool &success);

QByteArray toBase32(const QByteArray &data);
QByteArray fromBase32(const QByteArray &data);

#endif


bool base32_encode(char *dest, quint32 destlen, const char *src, quint32 srclen);
bool base32_decode(char *dest, quint32 destlen, const char *src, quint32 srclen);


}

#endif // TORUTILITY_H
