#include "rwlock.h"

//Allow as may readers possible, allows writer to starve
void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  rw->writers = 0;
  rw->readers = 0;
  rw->currently_writing = false;
  pthread_mutex_init(&rw->lock, NULL);
  pthread_cond_init(&rw->access, NULL);
}

void ReaderLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);

  while(rw->writers > 0 || rw->currently_writing){
    pthread_cond_wait(&rw->access, &rw->lock); // wait for writers to be done writing
  }
  rw->readers++;

  pthread_mutex_unlock(&rw->lock);
}

void ReaderUnlock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);

  rw->readers--;
  if(rw->readers == 0){
    pthread_cond_broadcast(&rw->access); // tell everyone that you are done reading
  }

  pthread_mutex_unlock(&rw->lock);
}

void WriterLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);

  rw->writers++;
  while(rw->readers > 0 || rw->currently_writing){
    pthread_cond_wait(&rw->access, &rw->lock); // wait for current readers to stop reading or for the current writer to stop writing.
  }
  rw->writers--;
  rw->currently_writing = true;

  pthread_mutex_unlock(&rw->lock);
}

void WriterUnlock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);

  rw->currently_writing = false;
  pthread_cond_broadcast(&rw->access); // tell everyone you are done wriring

  pthread_mutex_unlock(&rw->lock);
}
