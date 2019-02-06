#include "torutility.h"

namespace torutility {

qint32 getBase32EncodedLength(qint32 bytes)
{
    qint32 bits = bytes * 8;
    qint32 length = bits / 5;
    if((bits % 5) > 0)
    {
        length++;
    }
    return length;
}

qint32 getBase32DecodedLength(qint32 bytes)
{
    qint32 bits = bytes * 5;
    qint32 length = bits / 8;
    return length;
}

std::string toBase32(const std::string &data, bool &success)
{
    std::string output(getBase32EncodedLength(data.length())+1,0);
    success = base32_encode(const_cast<char*>(output.data()),
                            static_cast<quint32>(output.length()),
                            data.data(),
                            static_cast<quint32> (data.length()));
    output.pop_back();
    return output;
}

std::string fromBase32(const std::string &data, bool &success)
{
    std::string output(getBase32DecodedLength(data.length())+1,0);
    success = base32_decode(const_cast<char*>(output.data()),
                            static_cast<quint32>(output.length()),
                            data.data(),
                            static_cast<quint32> (data.length()));
    output.pop_back();
    return output;
}

std::string toBase32(const std::string &data)
{
    bool b = false;
    std::string out = toBase32(data,b);
    if(b)
    {
        return out;
    }
    else
    {
        out.clear();
        return out;
    }
}

std::string fromBase32(const std::string &data)
{
    bool b = false;
    std::string out = fromBase32(data,b);
    if(b)
    {
        return out;
    }
    else
    {
        out.clear();
        return out;
    }
}


#ifdef QT_CORE_LIB

QByteArray toBase32(const QByteArray &data, bool &success)
{
    QByteArray output(getBase32EncodedLength(data.length())+1,0);
    success = base32_encode(output.data(),
                            static_cast<quint32>(output.length()),
                            data.data(),
                            static_cast<quint32> (data.length()));
    output.chop(1);
    return output;
}

QByteArray fromBase32(const QByteArray &data, bool &success)
{
    QByteArray output(getBase32DecodedLength(data.length())+1,0);
    success = base32_decode(output.data(),
                            static_cast<quint32>(output.length()),
                            data.data(),
                            static_cast<quint32> (data.length()));
    output.chop(1);
    return output;
}

QByteArray toBase32(const QByteArray &data)
{
    bool b = false;
    QByteArray out = toBase32(data,b);
    if(b)
    {
        return out;
    }
    else
    {
        out.clear();
        return out;
    }
}

QByteArray fromBase32(const QByteArray &data)
{
    bool b = false;
    QByteArray out = fromBase32(data,b);
    if(b)
    {
        return out;
    }
    else
    {
        out.clear();
        return out;
    }
}


#endif



/* Copyright (c) 2001-2004, Roger Dingledine
 * Copyright (c) 2004-2006, Roger Dingledine, Nick Mathewson
 * Copyright (c) 2007-2010, The Tor Project, Inc.
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

#define BASE32_CHARS "abcdefghijklmnopqrstuvwxyz234567"


/* Implements base32 encoding as in rfc3548. Requires that srclen*8 is a multiple of 5. */
bool base32_encode(char *dest, quint32 destlen, const char *src, quint32 srclen)
{
    quint32 i, bit, v, u;
    quint32 nbits = srclen * 8;

    /* We need an even multiple of 5 bits, and enough space */
    if ((nbits%5) != 0 || destlen > (nbits/5)+1) {
        memset(dest, 0, destlen);
        return false;
    }

    for (i = 0, bit = 0; bit < nbits; ++i, bit += 5)
    {
        /* set v to the 16-bit value starting at src[bits/8], 0-padded. */
        v = ((quint8) src[bit / 8]) << 8;
        if (bit + 5 < nbits)
            v += (quint8) src[(bit/8)+1];

        /* set u to the 5-bit value at the bit'th bit of src. */
        u = (v >> (11 - (bit % 8))) & 0x1F;
        dest[i] = BASE32_CHARS[u];
    }

    dest[i] = '\0';
    return true;
}

/* Implements base32 decoding as in rfc3548. Requires that srclen*5 is a multiple of 8. */
bool base32_decode(char *dest, quint32 destlen, const char *src, quint32 srclen)
{
    quint32 i, j, bit;
    quint32 nbits = srclen * 5;

    /* We need an even multiple of 8 bits, and enough space */
    if ((nbits%8) != 0 || (nbits/8)+1 > destlen)
    {
        return false;
    }

    char *tmp = new char[srclen];

    /* Convert base32 encoded chars to the 5-bit values that they represent. */
    for (j = 0; j < srclen; ++j)
    {
        if (src[j] > 0x60 && src[j] < 0x7B)
            tmp[j] = src[j] - 0x61;
        else if (src[j] > 0x31 && src[j] < 0x38)
            tmp[j] = src[j] - 0x18;
        else if (src[j] > 0x40 && src[j] < 0x5B)
            tmp[j] = src[j] - 0x41;
        else
        {
            delete[] tmp;
            return false;
        }
    }

    /* Assemble result byte-wise by applying five possible cases. */
    for (i = 0, bit = 0; bit < nbits; ++i, bit += 8)
    {
        switch (bit % 40)
        {
        case 0:
            dest[i] = (((quint8)tmp[(bit/5)]) << 3) + (((quint8)tmp[(bit/5)+1]) >> 2);
            break;
        case 8:
            dest[i] = (((quint8)tmp[(bit/5)]) << 6) + (((quint8)tmp[(bit/5)+1]) << 1)
                    + (((quint8)tmp[(bit/5)+2]) >> 4);
            break;
        case 16:
            dest[i] = (((quint8)tmp[(bit/5)]) << 4) + (((quint8)tmp[(bit/5)+1]) >> 1);
            break;
        case 24:
            dest[i] = (((quint8)tmp[(bit/5)]) << 7) + (((quint8)tmp[(bit/5)+1]) << 2)
                    + (((quint8)tmp[(bit/5)+2]) >> 3);
            break;
        case 32:
            dest[i] = (((quint8)tmp[(bit/5)]) << 5) + ((quint8)tmp[(bit/5)+1]);
            break;
        }
    }

    delete[] tmp;
    return true;
}

}
