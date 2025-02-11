Releases history
----------------

Version 1.1.4
~~~~~~~~~~~~~

- The module works correctly in embedded Python.
- ``setproctitle()`` accepts a keyword argument.
- Debug output support always compiled in: the variable ``SPT_DEBUG`` can be
  used to emit debug log.


Version 1.1.3
~~~~~~~~~~~~~

- Don't clobber environ if the variable ``SPT_NOENV`` is set (issue #16).


Version 1.1.2
~~~~~~~~~~~~~

- Find the setproctitle include file on OpenBSD (issue #11).
- Skip test with unicode if the file system encoding wouldn't make it pass
  (issue #13).


Version 1.1.1
~~~~~~~~~~~~~

- Fixed segfault when the module is imported under mod_wsgi (issue #9).


Version 1.1
~~~~~~~~~~~

- The module works correctly with Python 3.


Version 1.0.1
~~~~~~~~~~~~~

- ``setproctitle()`` works even when Python messes up with argv, e.g. when run
  with the -m option (issue #8).


Version 1.0
~~~~~~~~~~~

No major change since the previous version.  The module has been heavily used
in production environment without any problem reported, so it's time to declare
it stable.


Version 0.4
~~~~~~~~~~~

- Module works on BSD (tested on FreeBSD 7.2).

- Module works on Windows. Many thanks to `Develer`_ for providing a neat `GCC
  package for Windows with Python integration`__ that made the Windows porting
  painless.

  .. _Develer: http://www.develer.com/
  .. __: http://www.develer.com/oss/GccWinBinaries


Version 0.3
~~~~~~~~~~~

- Module works on Mac OS X 10.2. Reported working on OS X 10.6 too.


Version 0.2
~~~~~~~~~~~

- Added ``prctl()`` call on Linux >= 2.6.9 to update ``/proc/self/status``.


Version 0.1
~~~~~~~~~~~

- Initial public release.
