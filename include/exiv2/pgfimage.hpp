// ***************************************************************** -*- C++ -*-
/*
 * Copyright (C) 2004-2018 Exiv2 authors
 * This program is part of the Exiv2 distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, 5th Floor, Boston, MA 02110-1301 USA.
 */
/*!
  @file    pgfimage.hpp
  @brief   PGF image, implemented using the following references:
           <a href="http://www.libpgf.org/uploads/media/PGF_stamm_wscg02.pdf">PGF specification</a> from libpgf web site<br>
  @author  Andreas Huggel (ahu)
           <a href="mailto:ahuggel@gmx.net">ahuggel@gmx.net</a>
  @author  Gilles Caulier (cgilles)
           <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
  @date    16-Jun-09, gc: submitted
 */
#pragma once

// *****************************************************************************
#include "exiv2lib_export.h"

// included header files
#include "image.hpp"

// *****************************************************************************
// namespace extensions
namespace Exiv2
{

// *****************************************************************************
// class definitions

    /*!
      @brief Class to access PGF images. Exif and IPTC metadata are supported
          directly.
     */
    class EXIV2API PgfImage : public Image {
    public:
        //! @name Creators
        //@{
        /*!
          @brief Constructor that can either open an existing PGF image or create
              a new image from scratch. If a new image is to be created, any
              existing data is overwritten. Since the constructor can not return
              a result, callers should check the good() method after object
              construction to determine success or failure.
          @param io An auto-pointer that owns a BasicIo instance used for
              reading and writing image metadata. \b Important: The constructor
              takes ownership of the passed in BasicIo instance through the
              auto-pointer. Callers should not continue to use the BasicIo
              instance after it is passed to this method.  Use the Image::io()
              method to get a temporary reference.
          @param create Specifies if an existing image should be read (false)
              or if a new file should be created (true).
         */
        PgfImage(BasicIo::UniquePtr io, bool create);
        //@}

        //! @name Manipulators
        //@{
        void readMetadata() override;
        void writeMetadata() override;
        //@}

        //! @name Accessors
        //@{
        std::string mimeType() const override { return "image/pgf"; }
        //@}

        PgfImage& operator=(const PgfImage& rhs) = delete;
        PgfImage& operator=(const PgfImage&& rhs) = delete;
        PgfImage(const PgfImage& rhs) = delete;
        PgfImage(const PgfImage&& rhs) = delete;

    private:
        bool bSwap_; // true for bigEndian hardware, else false
        /*!
          @brief Provides the main implementation of writeMetadata() by
                writing all buffered metadata to the provided BasicIo.
          @param oIo BasicIo instance to write to (a temporary location).

          @return 4 if opening or writing to the associated BasicIo fails
         */
        void doWriteMetadata(BasicIo& outIo);
        //! Read Magick number. Only version >= 6 is supported.
        static byte readPgfMagicNumber(BasicIo& iIo);
        //! Read PGF Header size encoded in 32 bits integer.
        uint32_t readPgfHeaderSize(BasicIo& iIo) const;
        //! Read header structure.
        DataBuf readPgfHeaderStructure(BasicIo& iIo, int& width, int& height) const;
        //@}

    }; // class PgfImage

// *****************************************************************************
// template, inline and free functions

    // These could be static private functions on Image subclasses but then
    // ImageFactory needs to be made a friend.
    /*!
      @brief Create a new PgfImage instance and return an auto-pointer to it.
             Caller owns the returned object and the auto-pointer ensures that
             it will be deleted.
     */
    EXIV2API Image::UniquePtr newPgfInstance(BasicIo::UniquePtr io, bool create);

    //! Check if the file iIo is a PGF image.
    EXIV2API bool isPgfType(BasicIo& iIo, bool advance);

}                                       // namespace Exiv2
