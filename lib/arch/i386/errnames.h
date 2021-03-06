#define NEPERM           "\x01" "EPERM"           "\0"
#define NENOENT          "\x02" "ENOENT"          "\0"
#define NESRCH           "\x03" "ESRCH"           "\0"
#define NEINTR           "\x04" "EINTR"           "\0"
#define NEIO             "\x05" "EIO"             "\0"
#define NENXIO           "\x06" "ENXIO"           "\0"
#define NE2BIG           "\x07" "E2BIG"           "\0"
#define NENOEXEC         "\x08" "ENOEXEC"         "\0"
#define NEBADF           "\x09" "EBADF"           "\0"
#define NECHILD          "\x0A" "ECHILD"          "\0"
#define NEAGAIN          "\x0B" "EAGAIN"          "\0"
#define NENOMEM          "\x0C" "ENOMEM"          "\0"
#define NEACCES          "\x0D" "EACCES"          "\0"
#define NEFAULT          "\x0E" "EFAULT"          "\0"
#define NENOTBLK         "\x0F" "ENOTBLK"         "\0"
#define NEBUSY           "\x10" "EBUSY"           "\0"
#define NEEXIST          "\x11" "EEXIST"          "\0"
#define NEXDEV           "\x12" "EXDEV"           "\0"
#define NENODEV          "\x13" "ENODEV"          "\0"
#define NENOTDIR         "\x14" "ENOTDIR"         "\0"
#define NEISDIR          "\x15" "EISDIR"          "\0"
#define NEINVAL          "\x16" "EINVAL"          "\0"
#define NENFILE          "\x17" "ENFILE"          "\0"
#define NEMFILE          "\x18" "EMFILE"          "\0"
#define NENOTTY          "\x19" "ENOTTY"          "\0"
#define NETXTBSY         "\x1A" "ETXTBSY"         "\0"
#define NEFBIG           "\x1B" "EFBIG"           "\0"
#define NENOSPC          "\x1C" "ENOSPC"          "\0"
#define NESPIPE          "\x1D" "ESPIPE"          "\0"
#define NEROFS           "\x1E" "EROFS"           "\0"
#define NEMLINK          "\x1F" "EMLINK"          "\0"
#define NEPIPE           "\x20" "EPIPE"           "\0"
#define NEDOM            "\x21" "EDOM"            "\0"
#define NERANGE          "\x22" "ERANGE"          "\0"
#define NEDEADLK         "\x23" "EDEADLK"         "\0"
#define NENAMETOOLONG    "\x24" "ENAMETOOLONG"    "\0"
#define NENOLCK          "\x25" "ENOLCK"          "\0"
#define NENOSYS          "\x26" "ENOSYS"          "\0"
#define NENOTEMPTY       "\x27" "ENOTEMPTY"       "\0"
#define NELOOP           "\x28" "ELOOP"           "\0"
#define NEWOULDBLOCK NEAGAIN
#define NENOMSG          "\x2A" "ENOMSG"          "\0"
#define NEIDRM           "\x2B" "EIDRM"           "\0"
#define NECHRNG          "\x2C" "ECHRNG"          "\0"
#define NEL2NSYNC        "\x2D" "EL2NSYNC"        "\0"
#define NEL3HLT          "\x2E" "EL3HLT"          "\0"
#define NEL3RST          "\x2F" "EL3RST"          "\0"
#define NELNRNG          "\x30" "ELNRNG"          "\0"
#define NEUNATCH         "\x31" "EUNATCH"         "\0"
#define NENOCSI          "\x32" "ENOCSI"          "\0"
#define NEL2HLT          "\x33" "EL2HLT"          "\0"
#define NEBADE           "\x34" "EBADE"           "\0"
#define NEBADR           "\x35" "EBADR"           "\0"
#define NEXFULL          "\x36" "EXFULL"          "\0"
#define NENOANO          "\x37" "ENOANO"          "\0"
#define NEBADRQC         "\x38" "EBADRQC"         "\0"
#define NEBADSLT         "\x39" "EBADSLT"         "\0"
#define NEDEADLOCK NEDEADLK
#define NEBFONT          "\x3B" "EBFONT"          "\0"
#define NENOSTR          "\x3C" "ENOSTR"          "\0"
#define NENODATA         "\x3D" "ENODATA"         "\0"
#define NETIME           "\x3E" "ETIME"           "\0"
#define NENOSR           "\x3F" "ENOSR"           "\0"
#define NENONET          "\x40" "ENONET"          "\0"
#define NENOPKG          "\x41" "ENOPKG"          "\0"
#define NEREMOTE         "\x42" "EREMOTE"         "\0"
#define NENOLINK         "\x43" "ENOLINK"         "\0"
#define NEADV            "\x44" "EADV"            "\0"
#define NESRMNT          "\x45" "ESRMNT"          "\0"
#define NECOMM           "\x46" "ECOMM"           "\0"
#define NEPROTO          "\x47" "EPROTO"          "\0"
#define NEMULTIHOP       "\x48" "EMULTIHOP"       "\0"
#define NEDOTDOT         "\x49" "EDOTDOT"         "\0"
#define NEBADMSG         "\x4A" "EBADMSG"         "\0"
#define NEOVERFLOW       "\x4B" "EOVERFLOW"       "\0"
#define NENOTUNIQ        "\x4C" "ENOTUNIQ"        "\0"
#define NEBADFD          "\x4D" "EBADFD"          "\0"
#define NEREMCHG         "\x4E" "EREMCHG"         "\0"
#define NELIBACC         "\x4F" "ELIBACC"         "\0"
#define NELIBBAD         "\x50" "ELIBBAD"         "\0"
#define NELIBSCN         "\x51" "ELIBSCN"         "\0"
#define NELIBMAX         "\x52" "ELIBMAX"         "\0"
#define NELIBEXEC        "\x53" "ELIBEXEC"        "\0"
#define NEILSEQ          "\x54" "EILSEQ"          "\0"
#define NERESTART        "\x55" "ERESTART"        "\0"
#define NESTRPIPE        "\x56" "ESTRPIPE"        "\0"
#define NEUSERS          "\x57" "EUSERS"          "\0"
#define NENOTSOCK        "\x58" "ENOTSOCK"        "\0"
#define NEDESTADDRREQ    "\x59" "EDESTADDRREQ"    "\0"
#define NEMSGSIZE        "\x5A" "EMSGSIZE"        "\0"
#define NEPROTOTYPE      "\x5B" "EPROTOTYPE"      "\0"
#define NENOPROTOOPT     "\x5C" "ENOPROTOOPT"     "\0"
#define NEPROTONOSUPPORT "\x5D" "EPROTONOSUPPORT" "\0"
#define NESOCKTNOSUPPORT "\x5E" "ESOCKTNOSUPPORT" "\0"
#define NEOPNOTSUPP      "\x5F" "EOPNOTSUPP"      "\0"
#define NENOTSUP NEOPNOTSUPP
#define NEPFNOSUPPORT    "\x60" "EPFNOSUPPORT"    "\0"
#define NEAFNOSUPPORT    "\x61" "EAFNOSUPPORT"    "\0"
#define NEADDRINUSE      "\x62" "EADDRINUSE"      "\0"
#define NEADDRNOTAVAIL   "\x63" "EADDRNOTAVAIL"   "\0"
#define NENETDOWN        "\x64" "ENETDOWN"        "\0"
#define NENETUNREACH     "\x65" "ENETUNREACH"     "\0"
#define NENETRESET       "\x66" "ENETRESET"       "\0"
#define NECONNABORTED    "\x67" "ECONNABORTED"    "\0"
#define NECONNRESET      "\x68" "ECONNRESET"      "\0"
#define NENOBUFS         "\x69" "ENOBUFS"         "\0"
#define NEISCONN         "\x6A" "EISCONN"         "\0"
#define NENOTCONN        "\x6B" "ENOTCONN"        "\0"
#define NESHUTDOWN       "\x6C" "ESHUTDOWN"       "\0"
#define NETOOMANYREFS    "\x6D" "ETOOMANYREFS"    "\0"
#define NETIMEDOUT       "\x6E" "ETIMEDOUT"       "\0"
#define NECONNREFUSED    "\x6F" "ECONNREFUSED"    "\0"
#define NEHOSTDOWN       "\x70" "EHOSTDOWN"       "\0"
#define NEHOSTUNREACH    "\x71" "EHOSTUNREACH"    "\0"
#define NEALREADY        "\x72" "EALREADY"        "\0"
#define NEINPROGRESS     "\x73" "EINPROGRESS"     "\0"
#define NESTALE          "\x74" "ESTALE"          "\0"
#define NEUCLEAN         "\x75" "EUCLEAN"         "\0"
#define NENOTNAM         "\x76" "ENOTNAM"         "\0"
#define NENAVAIL         "\x77" "ENAVAIL"         "\0"
#define NEISNAM          "\x78" "EISNAM"          "\0"
#define NEREMOTEIO       "\x79" "EREMOTEIO"       "\0"
#define NEDQUOT          "\x7A" "EDQUOT"          "\0"
#define NENOMEDIUM       "\x7B" "ENOMEDIUM"       "\0"
#define NEMEDIUMTYPE     "\x7C" "EMEDIUMTYPE"     "\0"
#define NECANCELED       "\x7D" "ECANCELED"       "\0"
#define NENOKEY          "\x7E" "ENOKEY"          "\0"
#define NEKEYEXPIRED     "\x7F" "EKEYEXPIRED"     "\0"
#define NEKEYREVOKED     "\x80" "EKEYREVOKED"     "\0"
#define NEKEYREJECTED    "\x81" "EKEYREJECTED"    "\0"
