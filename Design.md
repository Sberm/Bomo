File
	File
        directory exploration
        read
        mmap
	Filter
        exclude certain files
Output
    Format
	    output format
    Mode
        output mode
            normal, counting, ...
Regex
	Engine
    Boyer Moore

Thread

Configuration
    format specifications, filter options
Shell completion


~~~~~~~~~~~~~Worker~~~~~~~~~~~~~~~~~
      Directory walking [Filter]
               |
             {Dir}
               |
       File walking [Filter]
               |
             {File}
               |
  Pattern matching within a file
               |
            {Result}
               |
        Formatter [Mode]
               |
         {Text Output}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


       Master
         |
-------Dispatch-----
|        |         |
Worker   Worker    Worker

Amount of workers: CPU * 2 (?)

Master worker walks the directory, putting files into queue for dispatching, so no threads are idle.


# Distributed bm

Local master - remote slave
master gather data from remote slaves

```sh
bm pattern /usr/local/include --remote
bm GET /var/log/nginx
```