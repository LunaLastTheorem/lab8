#include "rwlock.h"

//Allow as may readers possible, allows writer to starve
void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  rw->readers = 0;
  pthread_mutex_init(&rw->lock, NULL);
  pthread_mutex_init(&rw->writer_lock, NULL);
}

void ReaderLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
  rw->readers++;
  if(rw->readers == 1){
    pthread_mutex_lock(&rw->writer_lock); //if its the first reader, adquire the rwlock
  }
  pthread_mutex_unlock(&rw->lock);
}

void ReaderUnlock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
  rw->readers--;
  if(rw->readers == 0){
    pthread_mutex_unlock(&rw->writer_lock);
  }
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
