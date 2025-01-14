//  This file is part of par2cmdline (a PAR 2.0 compatible file verification and
//  repair tool). See http://parchive.sourceforge.net for details of PAR 2.0.
//
//  Copyright (c) 2003 Peter Brian Clements
//  Copyright (c) 2019 Michael D. Nahas
//
//  par2cmdline is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  par2cmdline is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef __DESCRIPTIONPACKET_H__
#define __DESCRIPTIONPACKET_H__

#include <par2/md5.h>
#include <par2/diskfile.h>
#include <par2/par2fileformat.h>
#include <par2/criticalpacket.h>
#include <string>

// The description packet records details about a file (including its name,
// size, and the Hash of both the whole file and the first 16k of the file).

namespace Par2
{

class DescriptionPacket : public CriticalPacket
{
public:
  // Construct the packet
  DescriptionPacket(void) {};
  ~DescriptionPacket(void) {};

public:
  // Construct the packet and store the filename and size.
  bool Create(std::string _filename, u64 _filesize);

  // Store the computed Hash values in the packet.
  void Hash16k(const MD5Hash &hash);
  void HashFull(const MD5Hash &hash);

  // Compute and return the file id hash from information in the packet
  void ComputeFileId(void);
  const MD5Hash& FileId(void) const;

  // Return the size of the file
  u64 FileSize(void) const;

public:
  // Load a description packet from a specified file
  bool Load(DiskFile *diskfile, u64 offset, PACKET_HEADER &header);

  // Return the name of the file
  std::string FileName(void) const;

  // Get the Hash values from the packet
  const MD5Hash& HashFull(void) const;
  const MD5Hash& Hash16k(void) const;

  // Used to encode characters we do not want, such as "\t" or ":".
  // Function is public for easier testing.
  static std::string UrlEncodeChar(char c);

  // Converts filename from local disk to how it will be encoded
  // in the Par2 file, and back again.
  static std::string TranslateFilenameFromLocalToPar2(std::ostream &sout, std::ostream &serr, const NoiseLevel noiselevel, std::string local_filename);
  static std::string TranslateFilenameFromPar2ToLocal(std::ostream &sout, std::ostream &serr, const NoiseLevel noiselevel, std::string par2_encoded_filename);
private:
  std::string filename;
};

// Get the file id from the packet
inline const MD5Hash& DescriptionPacket::FileId(void) const
{
  assert(packetdata != 0);

  return ((const FILEDESCRIPTIONPACKET*)packetdata)->fileid;
}

// Get the size of the file from the packet
inline u64 DescriptionPacket::FileSize(void) const
{
  assert(packetdata != 0);

  return ((const FILEDESCRIPTIONPACKET*)packetdata)->length;
}

// Get the name of the file from the packet
// NB whilst the file format does not guarantee that the name will have a NULL
// termination character, par2cmdline always allocates a little extra data
// and fills it with NULLs to allow the filename to be directly read out of
// the packet.
inline std::string DescriptionPacket::FileName(void) const
{
  assert(packetdata != 0);

//  return (char*)((const FILEDESCRIPTIONPACKET*)packetdata)->name();
  return filename;
}

// Get the full file hash value from the packet
inline const MD5Hash& DescriptionPacket::HashFull(void) const
{
  assert(packetdata != 0);

  return ((const FILEDESCRIPTIONPACKET*)packetdata)->hashfull;
}

// The hash of the first 16k of the file from the packet
inline const MD5Hash& DescriptionPacket::Hash16k(void) const
{
  assert(packetdata != 0);

  return ((const FILEDESCRIPTIONPACKET*)packetdata)->hash16k;
}

}

#endif // __DESCRIPTIONPACKET_H__
