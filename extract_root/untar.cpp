#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <iostream>
#include <cstring>

auto copy_data(struct archive* a_read, struct archive* a_write) -> int
{
  const size_t buffer_size = 10240;  // Buffer size for copying data
  char buffer[buffer_size];
  const void* buff;
  size_t size = 0;
  int64_t offset = 0;

  for (;;)
  {
    auto result_read = archive_read_data_block(a_read, &buff, &size, &offset);
    if (result_read == ARCHIVE_EOF)
      return ARCHIVE_OK;
    if (result_read != ARCHIVE_OK)
    {
      return result_read;
    }
    // Copy the data from const void* to char* buffer using std::memcpy
    std::memcpy(buffer, buff, size);

    auto result_write = archive_write_data_block(a_write, buffer, size, offset);
    if (result_write != ARCHIVE_OK)
    {
      return result_write;
    }
  }
}

auto extract_nested_tar(const char* tar_file, const char* f_file) -> bool
{
  int result = 0;
  struct archive* archive;
  struct archive* ext;
  struct archive_entry* entry;
  std::string archive_entrypath;
  std::string nested_tar_data;  // Store nested tar data

  archive = archive_read_new();
  ext = archive_write_disk_new();

  archive_read_support_filter_all(archive);
  archive_read_support_format_all(archive);

  archive_write_disk_set_standard_lookup(ext);

  if (result = archive_read_open_filename(archive, tar_file, 10240))
  {
    std::cout << "failed to open a file = " << archive_error_string(archive) << std::endl;
    archive_read_free(archive);
    archive_write_free(ext);
    return false;
  }

  while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
  {
    archive_entrypath = archive_entry_pathname(entry);
    if (std::string::npos != archive_entrypath.find(f_file))
    {
      result = archive_write_header(ext, entry);
      if (result != ARCHIVE_OK)
      {
        std::cout << "failed to write header = " << archive_error_string(ext) << std::endl;
        archive_read_close(archive);
        archive_read_free(archive);
        archive_write_close(ext);
        archive_write_free(ext);
        return false;
      }
      else
      {
        result = copy_data(archive, ext);
        if (result != ARCHIVE_OK)
        {
          std::cout << "failed to copy data = " << archive_error_string(archive) << std::endl;
          archive_read_close(archive);
          archive_read_free(archive);
          archive_write_close(ext);
          archive_write_free(ext);
          return false;
        }
      }
      // Print the path of the root.meta file
      std::cout << "root.meta file found at path: " << archive_entrypath << std::endl;
      break;
    }
    else if (archive_entry_filetype(entry) == AE_IFREG && archive_entry_size(entry) > 0)
    {
      // Read the entire nested tar file into memory
      nested_tar_data.clear();
      const void* buff;
      size_t size = 0;
      int64_t offset = 0;

      for (;;)
      {
        auto result_read = archive_read_data_block(archive, &buff, &size, &offset);
        if (result_read == ARCHIVE_EOF)
          break;
        if (result_read < ARCHIVE_OK)
        {
          std::cout << "failed to read nested data = " << archive_error_string(archive) << std::endl;
          archive_read_close(archive);
          archive_read_free(archive);
          archive_write_close(ext);
          archive_write_free(ext);
          return false;
        }

        nested_tar_data.append(static_cast<const char*>(buff), size);
      }

      // Open the nested tar file from memory using archive_read_open_memory
      struct archive* n_archive = archive_read_new();
      archive_read_support_filter_all(n_archive);
      archive_read_support_format_all(n_archive);

      if (result = archive_read_open_memory(n_archive, nested_tar_data.data(), nested_tar_data.size()))
      {
        std::cout << "failed to open nested file from memory = " << archive_error_string(n_archive) << std::endl;
        archive_read_close(archive);
        archive_read_free(archive);
        archive_write_close(ext);
        archive_write_free(ext);
        archive_read_close(n_archive);
        archive_read_free(n_archive);
        return false;
      }

      // Extract the contents of the nested tar file
      while (archive_read_next_header(n_archive, &entry) == ARCHIVE_OK)
      {
        archive_entrypath = archive_entry_pathname(entry);
        if (std::string::npos != archive_entrypath.find(f_file))
        {
          result = archive_write_header(ext, entry);
          if (result != ARCHIVE_OK)
          {
            std::cout << "failed to write header = " << archive_error_string(ext) << std::endl;
            archive_read_close(archive);
            archive_read_free(archive);
            archive_write_close(ext);
            archive_write_free(ext);
            archive_read_close(n_archive);
            archive_read_free(n_archive);
            return false;
          }
          else
          {
            result = copy_data(n_archive, ext);
            if (result != ARCHIVE_OK)
            {
              std::cout << "failed to copy data = " << archive_error_string(n_archive) << std::endl;
              archive_read_close(archive);
              archive_read_free(archive);
              archive_write_close(ext);
              archive_write_free(ext);
              archive_read_close(n_archive);
              archive_read_free(n_archive);
              return false;
            }
          }
          // Print the path of the root.meta file
          std::cout << "root.meta file found at path: " << archive_entrypath << std::endl;
          break;
        }
        else
        {
          // For other files in the nested tar, skip extraction
          archive_read_data_skip(n_archive);
        }
      }

      archive_read_close(n_archive);
      archive_read_free(n_archive);
    }
  }

  archive_read_close(archive);
  archive_read_free(archive);

  archive_write_close(ext);
  archive_write_free(ext);
  return true;
}

int main()
{
  const char* zipPath = "valid-update-container-UC_SIGNED.tar";
  const char* filename = "root.meta";  // Provide the filename you want to extract

  extract_nested_tar(zipPath, filename);

  return 0;
}
