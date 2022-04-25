namespace app_models
{

    StepSequence::StepSequence(juce::ValueTree v)
    : state(v),
      channelList(v)
    {
        jassert(v.hasType(IDs::STEP_SEQUENCE));

        // if we have an empty sequence we need to initialize it
        if (channelList.isEmpty())
        {

            for (int i = 0; i < StepChannel::maxNumberOfChannels; i++)
            {

                juce::ValueTree channelTree(IDs::STEP_CHANNEL);
                channelTree.setProperty(IDs::stepChannelIndex, i, nullptr);
                channelTree.setProperty(IDs::stepPattern, "0000000000000000", nullptr);

                state.addChild(channelTree, -1, nullptr);

            }

        }

    }

    StepChannel* StepSequence::getChannel(int index)
    {

        for (auto channel : channelList.objects)
            if (channel->getIndex() == index)
                return channel;

        return nullptr;

    }

}
