/*
 * inspired by std::lockguard
 * when this object goes out of scope
 * the destructor will close a file opened
 */

class AbstractFile;
class AbstractFileSystem;
class CloseGuard
{
public:
  AbstractFileSystem* fs;
  AbstractFile* file;
  CloseGuard(AbstractFileSystem*, AbstractFile*);
  ~CloseGuard();
};
