#include "rwlock.h"

//Allow as may readers possible, allows writer to starve
void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  rw->readers = 0;
  pthread_mutex_init(&rw->lock, NULL);
  pthread_mutex_init(&rw->writer_lock, NULL);
  pthread_cond_init(&rw->writer_done, NULL);
}

void ReaderLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
  pthread_mutex_unlock(&rw->lock);
}

void ReaderUnlock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
  pthread_mutex_unlock(&rw->lock);
}

void WriterLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->writer_lock);
}

void WriterUnlock(struct read_write_lock * rw)
{
  pthread_mutex_unlock(&rw->writer_lock);
}
