 * Copyright (C) 2009-20 by RStudio, PBC
namespace rstudio {
namespace core {
namespace system {

class User;

}
}
}
#ifndef _WIN32

/**
 * @enum FileMode
 * Represents all possible posix file modes.
 */
enum class FileMode
{
   USER_READ_WRITE,
   USER_READ_WRITE_EXECUTE,
   USER_READ_WRITE_GROUP_READ,
   USER_READ_WRITE_ALL_READ,
   USER_READ_WRITE_EXECUTE_ALL_READ_EXECUTE,
   ALL_READ,
   ALL_READ_WRITE,
   ALL_READ_WRITE_EXECUTE
};

#endif

#ifdef _WIN32

    * @brief Creates a randomly named file in the temp directory.
    * @param out_filePath   The absolute path of the newly created file, or an empty file path if the file could not be
    *                       created.
    *
    * @return Success if the file could be created; Error otherwise.
    */
   static Error tempFilePath(FilePath& out_filePath);

   /**
    * @brief Creates a randomly named file with the specified extension in the temp directory.
    * @brief Creates a file with a random name in the specified directory.
    * @param in_basePath    The path at which to create the file.
    * @param out_filePath   The absolute path of the newly created file, or an empty file path if the file could not be
    *                       created.
    *
    * @return Success if the file could be created; Error otherwise.
    */
   static Error uniqueFilePath(const std::string& in_basePath, FilePath& out_filePath);

   /**
    * @brief Creates a file with a random name and the specified extension in the specified directory.
    */
   static Error uniqueFilePath(const std::string& in_basePath, const std::string& in_extension, FilePath& out_filePath);

#ifndef _WIN32
   /**
    * @brief Changes the file mode to the specified file mode.
    * @param in_fileModeStr     The posix file mode string. e.g. rwxr-xr-x.
    *
    * @return Success if the file mode could be changed; Error otherwise.
   Error changeFileMode(const std::string& in_fileModeStr) const;

   /**
    * @brief Changes the file mode to the specified file mode.
    *
    * @param in_fileMode        The new file mode.
    * @param in_setStickyBit    Whether to set the sticky bit on this file.
    *
    * @return Success if the file mode could be changed; Error otherwise.
    */
   Error changeFileMode(FileMode in_fileMode, bool in_setStickyBit = false) const;

   /**
    * @brief Changes the ownership of the file or directory to the specified user.
    *
    * @param in_newUser         The user who should own the file.
    * @param in_recursive       If this FilePath is a directory, whether to recursively change ownership on all files
    *                           and directories within this directory.
    * @param in_shouldChown     A recursive iteration function which allows the caller to filter files and directories.
    *                           If a file or directory should have its ownership changed, this function should return
    *                           true.
    *
    * @return Success if the file, and optionally all nested files and directories, had their ownership changed; Error
    *         otherwise.
    */
   Error changeOwnership(
      const system::User& in_newUser,
      bool in_recursive = false,
      const RecursiveIterationFunction& in_shouldChown = RecursiveIterationFunction()) const;
#endif
#ifdef _WIN32
#ifndef _WIN32
   /**
    * @brief Gets the posix file mode of this file or directory.
    *
    * @param out_fileMode   The file mode of this file or directory. Invalid if an error is returned.
    *
    * @return Success if the file mode could be retrieved; Error otherwise.
    */
   Error getFileMode(FileMode& out_fileMode) const;
#endif

#ifndef _WIN32

   /**
    * @brief Checks whether this file path is readable.
    *
    * @param out_readable       True if this file path is readable by the current effective user; false if it is not.
    *                           Invalid if this method returns an error.
    *
    * @return Success if the readability of this file could be checked; Error otherwise. (e.g. EACCES).
    */
   Error isReadable(bool& out_readable) const;

#endif

#ifndef _WIN32

   /**
    * @brief Checks whether this file path is writeable.
    *
    * @param out_writeable      True if this file path is writeable by the current effective user; false if it is not.
    *                           Invalid if this method returns an error.
    *
    * @return Success if the writeability of this file could be checked; Error otherwise. (e.g. EACCES).
    */
   Error isWriteable(bool& out_writeable) const;

#endif

   /**
    * @brief Checks if a file can be written to by opening the file.
    *
    * To be successful, the file must already exist on the system.
    * If write access is not absolutely necessary, use isWriteable instead.
    *
    * @return Success if file can be written to; system error otherwise (e.g. EPERM, ENOENT, etc.)
    */
   Error testWritePermissions() const;


/**
 * @brief Struct which implements the deleter for PathScopeImpl.
 */
struct PathScopeImplDeleter
{
   /**
    * @brief Deletion operator.
    */
   void operator()(PathScopeImpl*);
};
   RemoveOnExitScope(FilePath in_restorePath, ErrorLocation in_location);
 * @param io_ostream         The output stream to which to write the FilePath.
std::ostream& operator<<(std::ostream& io_ostream, const FilePath& in_filePath);
 * @brief Error creation function to be used when a file or directory exists but it should not.
 *
 * @param in_location   The location at which the error occurred.
 * @return The "file exists" error.
 */
Error fileExistsError(const ErrorLocation& in_location);

/**
 * @brief Error creation function to be used when a file could not be found.
 *
 * @param in_location   The location at which the error occurred.
 * @return The "file not found" error.
 */
Error fileNotFoundError(const ErrorLocation& in_location);

/**

/**
 * @brief Error creation function to be used when a file could not be found.
 *
 * @param in_filePath   The file which could not be found.
 * @param in_location   The location at which the error occurred.
 *
 * @return The "file not found" error.
 */
/**
 * @brief Error creation function to be used when a directory could not be found.
 *
 * @param in_filePath   The directory which could not be found.
 * @param in_location   The location at which the error occurred.
 *
 * @return The "path not found" error.
 */
Error pathNotFoundError(const std::string& in_filePath, const ErrorLocation& in_location);