#pragma once

template<typename T>
T&& Move(T& Obj)
{
	return Obj;
}

