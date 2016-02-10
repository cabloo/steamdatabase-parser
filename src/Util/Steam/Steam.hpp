namespace Util {
namespace Steam {
typedef unsigned long long Id32;
typedef const char * Id64;
/**
 * Convert a 32 bit SteamID into a 64 bit one.
 * @param  int id
 * @return the 64bit steam ID as a c-string
 */
Id64 to64Bit(Id32 id);

/**
 * Convert a 64 bit SteamID into a 32 bit one.
 * @param  char* id
 * @return an integer representation of the id
 */
Id32 to32Bit(Id64 id);
}
}
