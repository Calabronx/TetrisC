#pragma once
#ifndef COLORS_H
#define COLORS_H

struct Color {
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
};

inline Color color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	result.a = a;
	return result;
}

const Color BASE_COLORS[] = {
    color(0x28, 0x28, 0x28, 0xFF),
    color(0x2D, 0x99, 0x99, 0xFF),
    color(0x99, 0x99, 0x2D, 0xFF),
    color(0x99, 0x2D, 0x99, 0xFF),
    color(0x2D, 0x99, 0x51, 0xFF),
    color(0x99, 0x2D, 0x2D, 0xFF),
    color(0x2D, 0x63, 0x99, 0xFF),
    color(0x99, 0x63, 0x2D, 0xFF)
};

const Color LIGHT_COLORS[] = {
    color(0x28, 0x28, 0x28, 0xFF),
    color(0x44, 0xE5, 0xE5, 0xFF),
    color(0xE5, 0xE5, 0x44, 0xFF),
    color(0xE5, 0x44, 0xE5, 0xFF),
    color(0x44, 0xE5, 0x7A, 0xFF),
    color(0xE5, 0x44, 0x44, 0xFF),
    color(0x44, 0x95, 0xE5, 0xFF),
    color(0xE5, 0x95, 0x44, 0xFF)
};

const Color DARK_COLORS[] = {
    color(0x28, 0x28, 0x28, 0xFF),
    color(0x1E, 0x66, 0x66, 0xFF),
    color(0x66, 0x66, 0x1E, 0xFF),
    color(0x66, 0x1E, 0x66, 0xFF),
    color(0x1E, 0x66, 0x36, 0xFF),
    color(0x66, 0x1E, 0x1E, 0xFF),
    color(0x1E, 0x42, 0x66, 0xFF),
    color(0x66, 0x42, 0x1E, 0xFF)
};


const Color RED = {
	color(0xFF,0x00,0x00,0xFF)
};

const Color ORANGE = {
	color(0xFF,0xA5,0x00,0xFF)
};

const Color GREEN = {
	color(0x00,0x80,0x00,0xFF)
};

const Color YELLOW = {
	color(0xFF,0xFF,0x00,0xFF)
};

const Color BLACK = {
	color(0x00,0x00,0x00,0xFF)
};

const Color WHITE = {
	color(0xFF,0xFF,0xFF,0xFF)
};

const Color BLUE = {
	color(0x00, 0x00, 0xFF, 0xFF)
}; 

const Color BARELY_BLACK = {
	color(22, 22, 22, 255)
};

const Color DARK_GREY = {
	color(44, 44, 44, 255)
};

#endif