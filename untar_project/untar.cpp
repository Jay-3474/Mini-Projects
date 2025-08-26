#include <iostream>
#include <archive.h>
#include <archive_entry.h>
#include <cstring>
#include <vector>

void errmsg(const char*);
void archive_close(struct archive* a, struct archive* ext);
int copy_data(struct archive*, struct archive*);
void msg(const char*);
void usage(void);

int main(int argc, const char** argv)
{
  const char* filename = NULL;
  std::vector<std::string> f_name;
  int flags, mode, opt, r, needcr = 0;
  struct archive* a;
  struct archive* ext;
  struct archive_entry* entry;
  std::string xyz;

  if (argc < 2)
    usage();

  mode = 'm';
  int verbose = 0;

  flags = ARCHIVE_EXTRACT_TIME;
  flags |= ARCHIVE_EXTRACT_PERM;
  flags |= ARCHIVE_EXTRACT_ACL;
  flags |= ARCHIVE_EXTRACT_FFLAGS;

  /* Among other sins, getopt(3) pulls in printf(3). */
  while (*++argv != NULL && **argv == '-')
  {
    const char* p = *argv + 1;

    while ((opt = *p++) != '\0')
    {
      switch (opt)
      {
        case 'f':
          filename = *++argv;
          break;
        case 't':
          if (NULL == filename)
            usage();
          mode = opt;
          break;
        case 'v':
          if (NULL == filename)
            usage();
          verbose++;
          break;
        case 'x':
          if (NULL == filename)
            usage();
          mode = opt;
          break;
        case 'X':
          if (NULL == filename)
            usage();
          while (*++argv)
          {
            f_name.push_back(*argv);
          }
          mode = opt;
          break;
        case 'C':
          if (NULL == filename)
            usage();
          f_name.push_back(*++argv);
          mode = opt;
          break;
        default:
          usage();
      }
    }
  }

  if (NULL == filename)
    usage();

  a = archive_read_new();
  ext = archive_write_disk_new();
  archive_write_disk_set_options(ext, flags);

  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);

  archive_write_disk_set_standard_lookup(ext);

  if (filename != NULL && strcmp(filename, "-") == 0)
    filename = NULL;

  if ((r = archive_read_open_filename(a, filename, 10240)))
  {
    errmsg(archive_error_string(a));
    errmsg("\n");
    exit(r);
  }

  switch (mode)
  {
    case 't':
      for (;;)
      {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
          break;
        if (r != ARCHIVE_OK)
        {
          errmsg(archive_error_string(a));
          errmsg("\n");
          exit(1);
        }
        std::cout << archive_entry_size(entry);
        msg(" ");
        msg(archive_entry_pathname(entry));
        msg(" ");
        needcr = 1;
        if (needcr)
          msg("\n");
      }
      break;
    case 'x':
      for (;;)
      {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
          break;
        if (r != ARCHIVE_OK)
        {
          errmsg(archive_error_string(a));
          errmsg("\n");
          exit(1);
        }
        if (verbose)
        {
          msg("x ");
          std::cout << archive_entry_size(entry);
          msg(" ");
          msg(archive_entry_pathname(entry));
          msg(" ");
          needcr = 1;
        }
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK)
        {
          errmsg(archive_error_string(a));
          needcr = 1;
        }
        else
        {
          r = copy_data(a, ext);
          if (r != ARCHIVE_OK)
            needcr = 1;
        }
        if (needcr)
          msg("\n");
      }
      break;
    case 'X':
      while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
      {
        for (int i = 0; i < f_name.size(); ++i)
        {
          xyz = archive_entry_pathname(entry);
          // if(xyz == f_name[i]){
          if (std::string::npos != xyz.find(f_name[i]))
          {
            if (verbose)
            {
              msg("x ");
              std::cout << archive_entry_size(entry);
              msg(" ");
              msg(archive_entry_pathname(entry));
              msg(" ");
              needcr = 1;
            }
            r = archive_write_header(ext, entry);
            if (r != ARCHIVE_OK)
            {
              errmsg(archive_error_string(a));
              needcr = 1;
            }
            else
            {
              r = copy_data(a, ext);
              if (r != ARCHIVE_OK)
                needcr = 1;
            }
            if (needcr)
              msg("\n");
          }
        }
      }
      break;
    case 'C':
      for (;;)
      {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
          break;
        if (r != ARCHIVE_OK)
        {
          errmsg(archive_error_string(a));
          errmsg("\n");
          exit(1);
        }

        const char* currentFile = archive_entry_pathname(entry);
        char fullOutputPath[100];
        strcpy(fullOutputPath, f_name[0].c_str());
        strcat(fullOutputPath, currentFile);
        archive_entry_set_pathname(entry, fullOutputPath);

        if (verbose)
        {
          msg("x ");
          std::cout << archive_entry_size(entry);
          msg(" ");
          msg(archive_entry_pathname(entry));
          msg(" ");
          needcr = 1;
        }

        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK)
        {
          errmsg(archive_error_string(a));
          needcr = 1;
        }
        else
        {
          r = copy_data(a, ext);
          if (r != ARCHIVE_OK)
            needcr = 1;
        }
        if (needcr)
          msg("\n");
      }
      break;
  }

  archive_close(a, ext);

  return (0);
}

void archive_close(struct archive* a, struct archive* ext)
{
  archive_read_close(a);
  archive_read_free(a);

  archive_write_close(ext);
  archive_write_free(ext);
}

int copy_data(struct archive* ar, struct archive* aw)
{
  int r;
  const void* buff;
  size_t size;
  int64_t offset;

  for (;;)
  {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_EOF)
      return (ARCHIVE_OK);
    if (r != ARCHIVE_OK)
    {
      errmsg(archive_error_string(ar));
      return (r);
    }

    r = archive_write_data_block(aw, buff, size, offset);
    if (r != ARCHIVE_OK)
    {
      errmsg(archive_error_string(ar));
      return (r);
    }
  }
}

void msg(const char* m)
{
  std::cout << m;
}

void errmsg(const char* m)
{
  if (m == NULL)
  {
    m = "Error: No error description provided.\n";
  }
  std::cout << m;
}

void usage(void)
{
  /* Many program options depend on compile options. */
  const char* m =
      "Usage: untar [-"
      "ftvxXC"
      "] [tar_file] [file(s)/folder]\n";
  errmsg(m);
  exit(1);
}
