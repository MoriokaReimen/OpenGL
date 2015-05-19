#pragma once

struct PNG
{
    virtual const unsigned char* getData() const = 0;
    virtual unsigned int getSize() const = 0;
};

struct ToyouraPNG : PNG
{
    static const unsigned char data[];
    static const unsigned int size;
    const unsigned char* getData() const override;
    unsigned int getSize() const override;
};
