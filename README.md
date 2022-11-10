# A C++ Matching Engine

An academic exercise in code profiling. For more details, see my website at 
https://www.jmjatlanta.com/index.php/2019/12/09/matching-engine-requirements/

A matching engine engine is used in the financial markets. Not only do the exchanges need them, anyone who wants to keep
track of the bids and offers must also implement one. With the large quantity of data leaving the exchanges, processing 
such data can easily overwhelm a PC's processor.

There are high-tech solutions. Often, splitting the task into smaller components will help. Specialized hardware is also
available.

At what point does this become needed? I would like to find out in this project.

The first task is to build a simple matching engine. I will then work to find the bottlenecks and tweak the code.

## Initial Results

As mentioned in the blog article sited above, I was surprised at the results. It seems I am always surprised when looking
at performance tuning a piece of code. It is easy to set your mind on a suspect, and then find supporting reasons to
continue with that suspicion.

In this case, the bottleneck is in std::map. I have tried to use an alternate allocator, but it helped only marginally.

What did help was optimizing the code with the `-O2` switch. It went from around 1 second to process 1 million records
to about 0.14 seconds. That is quite a difference.

I doubt a custom std::map would help much. Placing the records in the correct location takes time. But 1 million records
is quite a number, and within the realm of possibilities for a particular security.

What are the options for increasing performance if necessary? Dedicated hardware. There are companies that have dedicated
their business to building order books on things like FPGAs. 

At times, you need to refer to multiple order books. Now you have other options. You can multithread, or even move the
job to other machines. And of course, hardware and software vendors have come up with specialized solutions for this as
well.

