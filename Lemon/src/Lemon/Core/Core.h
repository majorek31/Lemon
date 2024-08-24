#pragma once

#ifdef LM_ASSERT(x) if (!(x)) { std::cerr << "Assertion failed! " << #x << "\n"; __debugbreak(); }